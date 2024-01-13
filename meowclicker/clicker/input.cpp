#include "input.hpp"
#include "gui.hpp"

#include <thread>
#include <cstdint>
#include <random>
#include <Windows.h>

namespace inputmath
{
	float getRandomFloat(const float min, const float max) noexcept
	{
		std::random_device                  rand_dev;
		std::mt19937                        gen(rand_dev());
		std::uniform_real_distribution<float>  dist(min, max);

		return dist(gen);
	}

	float cpsToDelay(const float cps) noexcept
	{
		return 1000 / cps;
	}
}

namespace input
{
	POINT mousePos{ 0, 0 };
	HWND foreground{ GetForegroundWindow() };

	void sendClick(const float blockChance, const bool rightClick) noexcept
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

	void sendJitter(const float jitterFactor) noexcept
	{
		float jitterX = inputmath::getRandomFloat(-jitterBase, jitterBase) * jitterFactor;
		float jitterY = inputmath::getRandomFloat(-jitterBase, jitterBase) * jitterFactor;

		mousePos.x += jitterX;
		mousePos.y += jitterY;

		SetCursorPos(mousePos.x, mousePos.y);
	}

	void clickLoop() noexcept
	{
		bool clicked = false;

		while (gui::isRunning)
		{
			float cps = inputmath::getRandomFloat(config::minCPS, config::maxCPS);
			int key = config::rightClick ? VK_RBUTTON : VK_LBUTTON;

			clicked = false;

			if (GetAsyncKeyState(key) && config::enabled && GetForegroundWindow() != gui::window)
			{
				// continue in loop if trying to click on non-minecraft window with "Minecraft Window Only" enabled
				if (config::mcWindow && GetForegroundWindow() != FindWindowA("LWJGL", nullptr)) 
					continue;

				input::sendClick(config::blockChance, config::rightClick);
				input::sendJitter(config::jitter);
				clicked = true;
			}

			if (clicked) // sleep for randomized amount of time if clicking
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<uint64_t>(inputmath::cpsToDelay(cps))));
			}
			else // else, update at same rate as GUI
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(gui::updateDelay));
			}
		}
	}
}