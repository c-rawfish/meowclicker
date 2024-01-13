#include "gui.hpp"
#include "input.hpp"

#include <thread>

int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	gui::createHWindow(gui::title);
	gui::createDevice();
	gui::createImGui();

	std::jthread clickThread(input::clickLoop);
	clickThread.detach();

	bool wasPressed = false;
	while (gui::isRunning)
	{
		gui::beginRender();
		gui::render();
		gui::endRender();

		if (GetAsyncKeyState(VK_F6))
		{
			if (!wasPressed)
			{
				wasPressed = true;
				config::enabled = !config::enabled;
			}
		}
		else { wasPressed = false; }

		std::this_thread::sleep_for(std::chrono::milliseconds(gui::updateDelay));
	}

	gui::destroyImGui();
	gui::destroyDevice();
	gui::destroyHWindow();

	return EXIT_SUCCESS;
}