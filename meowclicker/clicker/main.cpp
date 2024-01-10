#include "gui.h"
#include "input.h"

#include <thread>
#include <iostream>

int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	gui::CreateHWindow("meowclicker v1.1");
	gui::CreateDevice();
	gui::CreateImGui();

	bool wasPressed = false;
	while (gui::isRunning)
	{
		gui::BeginRender();
		gui::Render();
		gui::EndRender();

		float cps = inputmath::getRandomFloat(config::minCPS, config::maxCPS + 1);

		if (GetAsyncKeyState(VK_F6) & 1 && !wasPressed)
		{
			wasPressed = true;
			config::enabled = !config::enabled;
		}
		else { wasPressed = false; }

		if (GetAsyncKeyState(VK_LBUTTON) && config::enabled && GetForegroundWindow() != gui::window)
		{
			if (config::mcWindow && GetForegroundWindow() != FindWindowA("LWJGL", nullptr))
				continue;

			input::sendClick(config::blockChance);
			input::sendJitter(config::jitter);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds((long)inputmath::cpsToDelay(cps)));
	}

	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	return EXIT_SUCCESS;
}