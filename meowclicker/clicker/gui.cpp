#include "gui.hpp"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"

#include <format>

// skidded from cazz

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter
);

long __stdcall WindowProcess(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter)
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, wideParameter, longParameter))
		return true;

	switch (message)
	{
	case WM_SIZE: {
		if (gui::device && wideParameter != SIZE_MINIMIZED)
		{
			gui::presentParameters.BackBufferWidth = LOWORD(longParameter);
			gui::presentParameters.BackBufferHeight = HIWORD(longParameter);
			gui::resetDevice();
		}
	}return 0;

	case WM_SYSCOMMAND: {
		if ((wideParameter & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
	}break;

	case WM_DESTROY: {
		PostQuitMessage(0);
	}return 0;

	case WM_LBUTTONDOWN: {
		gui::position = MAKEPOINTS(longParameter); // set click points
	}return 0;

	case WM_MOUSEMOVE: {
		if (wideParameter == MK_LBUTTON)
		{
			const auto points = MAKEPOINTS(longParameter);
			auto rect = ::RECT{ };

			GetWindowRect(gui::window, &rect);

			rect.left += points.x - gui::position.x;
			rect.top += points.y - gui::position.y;

			if (gui::position.x >= 0 &&
				gui::position.x <= gui::WIDTH &&
				gui::position.y >= 0 && gui::position.y <= 19)
				SetWindowPos(
					gui::window,
					HWND_TOPMOST,
					rect.left,
					rect.top,
					0, 0,
					SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER
				);
		}

	}return 0;

	}

	return DefWindowProc(window, message, wideParameter, longParameter);
}

namespace gui
{
	void createHWindow(const char* windowName) noexcept
	{
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_CLASSDC;
		windowClass.lpfnWndProc = WindowProcess;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = GetModuleHandleA(0);
		windowClass.hIcon = 0;
		windowClass.hCursor = 0;
		windowClass.hbrBackground = 0;
		windowClass.lpszMenuName = 0;
		windowClass.lpszClassName = "class001";
		windowClass.hIconSm = 0;

		RegisterClassEx(&windowClass);

		window = CreateWindowEx(
			0,
			"class001",
			windowName,
			WS_POPUP,
			100,
			100,
			WIDTH,
			HEIGHT,
			0,
			0,
			windowClass.hInstance,
			0
		);

		ShowWindow(window, SW_SHOWDEFAULT);
		UpdateWindow(window);
	}

	void destroyHWindow() noexcept
	{
		DestroyWindow(window);
		UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
	}

	bool createDevice() noexcept
	{
		d3d = Direct3DCreate9(D3D_SDK_VERSION);

		if (!d3d)
			return false;

		ZeroMemory(&presentParameters, sizeof(presentParameters));

		presentParameters.Windowed = TRUE;
		presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
		presentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
		presentParameters.EnableAutoDepthStencil = TRUE;
		presentParameters.AutoDepthStencilFormat = D3DFMT_D16;
		presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

		if (d3d->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			window,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&presentParameters,
			&device) < 0)
			return false;

		return true;
	}

	void resetDevice() noexcept
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();

		const auto result = device->Reset(&presentParameters);

		if (result == D3DERR_INVALIDCALL)
			IM_ASSERT(0);

		ImGui_ImplDX9_CreateDeviceObjects();
	}

	void destroyDevice() noexcept
	{
		if (device)
		{
			device->Release();
			device = nullptr;
		}

		if (d3d)
		{
			d3d->Release();
			d3d = nullptr;
		}
	}

	void createImGui() noexcept
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ::ImGui::GetIO();

		io.IniFilename = NULL;

		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX9_Init(device);
	}

	void destroyImGui() noexcept
	{
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void beginRender() noexcept
	{
		MSG message;
		while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);

			if (message.message == WM_QUIT)
			{
				isRunning = !isRunning;
				return;
			}
		}

		// Start the Dear ImGui frame
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void endRender() noexcept
	{
		ImGui::EndFrame();

		device->SetRenderState(D3DRS_ZENABLE, FALSE);
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

		device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

		if (device->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			device->EndScene();
		}

		const auto result = device->Present(0, 0, 0, 0);

		// Handle loss of D3D9 device
		if (result == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
			resetDevice();
	}

	bool waitingForHotkey = false;
	int tab = 0;

	void renderBasicTab(config::Clicker* clicker) noexcept // renders the basic settings of a clicker tab
	{
		ImGui::Checkbox("enabled", &clicker->enabled);
		ImGui::Checkbox("minecraft window only", &clicker->mcWindow);
		ImGui::Text(std::format("hold {} when enabled to autoclick", &clicker->rightClick ? "rmb" : "lmb").c_str());
		ImGui::Text(std::format("press {} to toggle enabled", &clicker->rightClick ? "f7" : "f6").c_str());

		ImGui::NewLine();

		ImGui::SliderFloat("min cps", &clicker->minCPS, 0, 20, "%.3f");
		ImGui::SliderFloat("max cps", &clicker->maxCPS, 0, 20, "%.3f");
		ImGui::SliderFloat("jitter", &clicker->jitter, 0, 2, "%.3f");

		if (clicker->minCPS > clicker->maxCPS)
		{
			clicker->maxCPS = clicker->minCPS;
		}
	}

	void render(std::vector<config::Clicker>* clickers) noexcept
	{
		ImGui::SetNextWindowPos({ 0, 0 });
		ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
		ImGui::Begin(
			title.c_str(),
			&isRunning,
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove
		);

		// dont ask me how i found out these values would work, it kinda centers the tabs but it might not be perfect so idk
		if (ImGui::Button("left clicker", ImVec2(100, 25))) { tab = 0; }
		ImGui::SameLine(100 + ImGui::GetStyle().FramePadding.x, 21);
		if (ImGui::Button("right clicker", ImVec2(100, 25))) { tab = 1; }
		ImGui::SameLine(216 + ImGui::GetStyle().FramePadding.x, 21);
		if (ImGui::Button("config", ImVec2(100, 25))) { tab = 2; }
		ImGui::Separator();

		switch (tab)
		{
		case 0: {
			config::Clicker* clicker = &clickers->at(0);
			renderBasicTab(clicker); // assumes the left clicker always comes first (which it does)
			ImGui::SliderFloat("blockhit chance", &clicker->blockChance, 0, 100, "%.3f");
			break;
		}
		case 1: {
			config::Clicker* clicker = &clickers->at(1);
			renderBasicTab(clicker);
			break;
		}
		case 2: {
			ImGui::Text("coming soon!");
			break;
		}
		}

		ImGui::End();
	}
}