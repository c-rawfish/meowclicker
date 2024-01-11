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
	gui::CreateHWindow("meowclicker v1.2");
	gui::CreateDevice();
	gui::CreateImGui();

	std::thread clickThread(input::clickLoop);

	bool wasPressed = false;
	while (gui::isRunning)
	{
		gui::BeginRender();
		gui::Render();
		gui::EndRender();

		if (GetAsyncKeyState(VK_F6))
		{
			if (!wasPressed)
			{
				wasPressed = true;
				config::enabled = !config::enabled;
			}
		}
		else { wasPressed = false; }

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	clickThread.detach();

	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	return EXIT_SUCCESS;
}