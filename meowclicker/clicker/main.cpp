#include "gui.hpp"
#include "input.hpp"

#include <thread>
#include <vector>

int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	config::Clicker leftClicker;

	config::Clicker rightClicker;
	rightClicker.key = VK_RBUTTON;
	rightClicker.toggleKey = VK_F7;
	rightClicker.blockChance = 0;
	rightClicker.rightClick = true;

	config::Clicker* current = &leftClicker;

	std::vector<config::Clicker> clickers;
	clickers.push_back(leftClicker);
	clickers.push_back(rightClicker);

	gui::createHWindow(gui::title.c_str());
	gui::createDevice();
	gui::createImGui();

	std::jthread clickThread(input::clickLoop, &clickers);
	clickThread.detach();

	bool wasPressed = false;
	while (gui::isRunning)
	{
		gui::beginRender();
		gui::render(&clickers);
		gui::endRender();

		if (GetAsyncKeyState(VK_F6))
		{
			if (!wasPressed)
			{
				wasPressed = true;
				current->enabled = !current->enabled;
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