#include "clicker.hpp"

#include "maths.hpp"
#include "gui.hpp"
#include "input.hpp"

#include <thread>

Clicker::Clicker(int key, int toggleKey, bool rightClick) : 
	mEnabled(false), mMCWindowOnly(false), mKey(key), mToggleKey(toggleKey), mRightClick(rightClick),
	mMinCPS(12), mMaxCPS(17), mJitter(0), mBlockChance(0)
{
	std::jthread clickThread(&Clicker::startClickLoop, this);
	clickThread.detach();
}

bool* Clicker::getEnabledPtr() { return &mEnabled; }
bool* Clicker::getMCWindowOnlyPtr() { return &mMCWindowOnly; }
float* Clicker::getMinCPSPtr() { return &mMinCPS; }
float* Clicker::getMaxCPSPtr() { return &mMaxCPS; }
float* Clicker::getJitterPtr() { return &mJitter; }
float* Clicker::getBlockChancePtr() { return &mBlockChance; }

// const values, never need a pointer returned (just the value for checks)
int Clicker::getKey() const { return mKey; }
int Clicker::getToggleKey() const { return mToggleKey; }
bool Clicker::getRightClick() const { return mRightClick; }

// only value ever being modified directly
void Clicker::setMaxCPS(float cps) { mMaxCPS = cps; }

void Clicker::startClickLoop()
{
	bool clicked = false;
	bool toggleKeyPressed = false;
	while (gui::isRunning)
	{
		float cps = maths::getRandomFloat(mMinCPS, mMaxCPS);
		HWND window = GetForegroundWindow();

		if (GetAsyncKeyState(mKey) && mEnabled && window != gui::window)
		{
			if (mMCWindowOnly && window != FindWindowA("LWJGL", nullptr))
				continue;

			input::sendClick(window, mRightClick);
			input::sendJitter(mJitter);
			clicked = true;
		}
		else { clicked = false; }

		if (GetAsyncKeyState(mToggleKey))
		{
			if (!toggleKeyPressed)
			{
				toggleKeyPressed = true;
				mEnabled = !mEnabled;
			}
		}
		else { toggleKeyPressed = false; }

		if (clicked) { maths::preciseSleep((1000 / cps) / 1000); }
		else { std::this_thread::sleep_for(std::chrono::milliseconds(gui::updateDelay)); }
	}
}