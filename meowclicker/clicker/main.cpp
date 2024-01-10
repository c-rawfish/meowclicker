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
	gui::CreateHWindow("meowclicker v1.0");
	gui::CreateDevice();
	gui::CreateImGui();

	while (gui::isRunning)
	{
		gui::BeginRender();
		gui::Render();
		gui::EndRender();

		float cps = inputmath::getRandomFloat(config::minCPS, config::maxCPS + 1);

		if (GetAsyncKeyState(VK_LBUTTON) && config::enabled && GetForegroundWindow() != gui::window)
		{
			input::sendClick();
			input::sendJitter(config::jitter);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds((long)inputmath::cpsToDelay(cps)));
	}

	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	return EXIT_SUCCESS;
}