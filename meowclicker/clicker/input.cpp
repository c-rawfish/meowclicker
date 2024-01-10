#include "input.h"

namespace inputmath
{
	int getRandomInt(int min, int max)
	{
		std::random_device                  rand_dev;
		std::mt19937                        gen(rand_dev());
		std::uniform_int_distribution<int>  dist(min, max + 1);

		return dist(gen);
	}

	float getRandomFloat(float min, float max)
	{
		std::random_device                  rand_dev;
		std::mt19937                        gen(rand_dev());
		std::uniform_real_distribution<float>  dist(min, max + 1);

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

	void sendClick(float blockChance)
	{
		GetCursorPos(&mousePos);
		foreground = GetForegroundWindow();

		LPARAM mouseParam = MAKELPARAM(mousePos.x, mousePos.y);
		
		PostMessageA(foreground, WM_LBUTTONDOWN, 0, mouseParam);
		if (inputmath::getRandomFloat(0, 100) < blockChance)
		{
			PostMessageA(foreground, WM_RBUTTONDOWN, 0, mouseParam);
			PostMessageA(foreground, WM_RBUTTONUP, 0, mouseParam);
		}
		PostMessageA(foreground, WM_LBUTTONUP, 0, mouseParam);
	}

	void sendJitter(float jitterFactor)
	{
		float jitterX = inputmath::getRandomFloat(-0.5F, 0.5F) * jitterFactor;
		float jitterY = inputmath::getRandomFloat(-0.5F, 0.5F) * jitterFactor;

		mousePos.x += jitterX;
		mousePos.y += jitterY;

		SetCursorPos(mousePos.x, mousePos.y);
	}
}