#include "gui.hpp"

#include "clicker.hpp"

#include <thread>

int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	Clicker leftClicker(VK_LBUTTON, VK_F6, false);
	Clicker rightClicker(VK_RBUTTON, VK_F7, true);

	gui::createHWindow(gui::title.c_str());
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