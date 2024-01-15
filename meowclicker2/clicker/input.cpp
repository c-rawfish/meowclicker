#include "input.hpp"

#include "maths.hpp"
#include "clicker.hpp"

#include <thread>

namespace input
{
	POINT mousePos;

	void sendClick(HWND window, bool rightClick) noexcept
	{
		GetCursorPos(&mousePos);

		LPARAM mouseParam = MAKELPARAM(mousePos.x, mousePos.y);

		if (rightClick)
		{
			PostMessageA(window, WM_RBUTTONDOWN, 0, mouseParam);
			PostMessageA(window, WM_RBUTTONUP, 0, mouseParam);
		}
		else
		{
			PostMessageA(window, WM_LBUTTONDOWN, 0, mouseParam);
			PostMessageA(window, WM_LBUTTONUP, 0, mouseParam);
		}
	}

	void sendJitter(float jitter) noexcept
	{
		float jitterX = maths::getRandomFloat(-jitterBase, jitterBase) * jitter;
		float jitterY = maths::getRandomFloat(-jitterBase, jitterBase) * jitter;

		mousePos.x += jitterX;
		mousePos.y += jitterY;

		SetCursorPos(mousePos.x, mousePos.y);
	}
}