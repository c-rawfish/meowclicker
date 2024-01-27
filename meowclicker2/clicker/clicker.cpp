#include "clicker.hpp"
#include "gui.hpp"
#include "math.hpp"

#include <thread>

Clicker::Clicker(bool rightClick, int toggleKey) : 
mEnabled(false), mMcWindowOnly(true), mRightClick(rightClick), mMouseKey(rightClick ? VK_RBUTTON : VK_LBUTTON),
mToggleKey(toggleKey), mMinCps(9), mMaxCps(14), mJitter(0)
{
	std::jthread clickThread(&Clicker::clickLoop, this);
	clickThread.detach();
}

void Clicker::sendClick(LPARAM mouseParam)
{
	HWND window = GetForegroundWindow();
	if (window == gui::window)
		return;

	if (mMcWindowOnly)
	{
		HWND mcWindow = FindWindowA("LWJGL", NULL);
		window = mcWindow != NULL ? mcWindow : window;
	}

	PostMessageA(window, mRightClick ? WM_RBUTTONDOWN : WM_LBUTTONDOWN, 0, mouseParam);
	PostMessageA(window, mRightClick ? WM_RBUTTONUP : WM_LBUTTONUP, 0, mouseParam);
}

void Clicker::clickLoop()
{
	POINT mousePos;
	bool toggleKeyPressed = false;

	while (gui::isRunning)
	{
		if (GetAsyncKeyState(mToggleKey))
		{
			if (!toggleKeyPressed)
			{
				toggleKeyPressed = true;
				mEnabled = !mEnabled;
			}
		}
		else { toggleKeyPressed = false; }

		if (GetAsyncKeyState(mMouseKey) && mEnabled)
		{
			long delay = 1000 / math::getRandomFloat(mMinCps, mMaxCps); // divide (1000 / random float) to get delay in milliseconds
			
			GetCursorPos(&mousePos);
			sendClick(MAKELPARAM(mousePos.x, mousePos.y));

			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
			continue;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(gui::updateDelay));
	}
}