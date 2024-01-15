#include "gui.hpp"
#include "input.hpp"
#include "config.hpp"

#include <thread>
#include <vector>

int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	Clicker leftClicker(VK_LBUTTON, VK_F6, false, 0);
	Clicker rightClicker(VK_RBUTTON, VK_F7, true, 0);

	std::vector<Clicker> clickers{ leftClicker, rightClicker };

	gui::createHWindow(gui::title.c_str());
	gui::createDevice();
	gui::createImGui();

	input::clickLoopSetup(std::ref(clickers));

	while (gui::isRunning)
	{
		gui::beginRender();
		gui::render(&clickers);
		gui::endRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(gui::updateDelay));
	}

	gui::destroyImGui();
	gui::destroyDevice();
	gui::destroyHWindow();

	return EXIT_SUCCESS;
}