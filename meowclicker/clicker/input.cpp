#include "input.h"
#include "gui.h"

#include <thread>

namespace inputmath
{
	float getRandomFloat(float min, float max)
	{
		std::random_device                  rand_dev;
		std::mt19937                        gen(rand_dev());
		std::uniform_real_distribution<float>  dist(min, max);

		return dist(gen);
	}

	float cpsToDelay(float cps)
	{
		return 1000 / cps;
	}
}

namespace input
{
	POINT mousePos{ 0, 0 };
	HWND foreground{ GetForegroundWindow() };

	void sendClick(float blockChance, bool rightClick)
	{
		GetCursorPos(&mousePos);
		foreground = GetForegroundWindow();

		LPARAM mouseParam = MAKELPARAM(mousePos.x, mousePos.y);
		
		PostMessageA(foreground, rightClick ? WM_RBUTTONDOWN : WM_LBUTTONDOWN, 0, mouseParam);
		if (!rightClick && inputmath::getRandomFloat(0, 100) < blockChance)
		{
			PostMessageA(foreground, WM_RBUTTONDOWN, 0, mouseParam);
			PostMessageA(foreground, WM_RBUTTONUP, 0, mouseParam);
		}
		PostMessageA(foreground, rightClick ? WM_RBUTTONUP : WM_LBUTTONUP, 0, mouseParam);
	}

	void sendJitter(float jitterFactor)
	{
		float jitterX = inputmath::getRandomFloat(-0.5F, 0.5F) * jitterFactor;
		float jitterY = inputmath::getRandomFloat(-0.5F, 0.5F) * jitterFactor;

		mousePos.x += jitterX;
		mousePos.y += jitterY;

		SetCursorPos(mousePos.x, mousePos.y);
	}

	void clickLoop()
	{
		while (gui::isRunning)
		{
			float cps = inputmath::getRandomFloat(config::minCPS, config::maxCPS + 1);
			bool clicked = false;

			if (GetAsyncKeyState(VK_LBUTTON) && config::enabled && GetForegroundWindow() != gui::window)
			{
				if (config::mcWindow && GetForegroundWindow() != FindWindowA("LWJGL", nullptr))
					continue;

				input::sendClick(config::blockChance, config::rightClick);
				input::sendJitter(config::jitter);
				clicked = true;
			}

			if (clicked) // sleep for randomized amount of time if clicking
			{
				std::this_thread::sleep_for(std::chrono::milliseconds((long)inputmath::cpsToDelay(cps)));
			}
			else // else, update at same rate as GUI
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(16));
			}
		}
	}
}