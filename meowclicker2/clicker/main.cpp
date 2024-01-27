#include "gui.hpp"
#include "clicker.hpp"

#include <thread>

int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	Clicker leftClicker(false, VK_F6);
	Clicker rightClicker(true, VK_F7);

	gui::createHWindow("meowclicker");
	gui::createDevice();
	gui::createImGui();

	while (gui::isRunning)
	{
		gui::beginRender();
		gui::render(&leftClicker, &rightClicker);
		gui::endRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(gui::updateDelay));
	}

	gui::destroyImGui();
	gui::destroyDevice();
	gui::destroyHWindow();

	return EXIT_SUCCESS;
}