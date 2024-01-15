#include "config.hpp"
#include "input.hpp"
#include <Windows.h>
#include <thread>

Clicker::Clicker(int key, int toggleKey, bool rightClick, float blockChance) :
	mEnabled(false), mKey(key), mToggleKey(toggleKey), mRightClick(rightClick), mMCWindowOnly(false), mMinCPS(12), mMaxCPS(17), mJitter(0), mBlockChance(blockChance)
{
	
}

bool Clicker::getEnabled() const { return mEnabled; }
int Clicker::getKey() const { return mKey; }
int Clicker::getToggleKey() const { return mToggleKey; }
bool Clicker::getRightClick() const { return mRightClick; }
bool Clicker::getMCWindowOnly() const { return mMCWindowOnly; }
float Clicker::getMinCPS() const { return mMinCPS; }
float Clicker::getMaxCPS() const { return mMaxCPS; }
float Clicker::getJitter() const { return mJitter; }
float Clicker::getBlockChance() const { return mBlockChance; }

bool* Clicker::getEnabledPtr() { return &mEnabled; }
int* Clicker::getKeyPtr() { return &mKey; }
int* Clicker::getToggleKeyPtr() { return &mToggleKey; }
bool* Clicker::getRightClickPtr() { return &mRightClick; }
bool* Clicker::getMCWindowOnlyPtr() { return &mMCWindowOnly; }
float* Clicker::getMinCPSPtr() { return &mMinCPS; }
float* Clicker::getMaxCPSPtr() { return &mMaxCPS; }
float* Clicker::getJitterPtr() { return &mJitter; }
float* Clicker::getBlockChancePtr() { return &mBlockChance; }

void Clicker::setEnabled(bool enabled) { mEnabled = enabled; }
void Clicker::setKey(int key) { mKey = key; }
void Clicker::setToggleKey(int toggleKey) { mToggleKey = toggleKey; }
void Clicker::setRightClick(bool rightClick) { mRightClick = rightClick; }
void Clicker::setMCWindowOnly(bool mcWindowOnly) { mMCWindowOnly = mcWindowOnly; }
void Clicker::setMinCPS(float minCPS) { mMinCPS = minCPS; }
void Clicker::setMaxCPS(float maxCPS) { mMaxCPS = maxCPS; }
void Clicker::setJitter(float jitter) { mJitter = jitter; }
void Clicker::setBlockChance(float blockChance) { mBlockChance = blockChance; }

void Clicker::clickLoop()
{
	float cps;
	bool clicked = false;
	bool wasPressed = false;

	while (gui::isRunning)
	{
		cps = inputmath::getRandomFloat(mMinCPS, mMaxCPS);

		if (GetAsyncKeyState(mKey) && mEnabled && GetForegroundWindow() != gui::window)
		{
			// continue in loop if trying to click on non-minecraft window with "Minecraft Window Only" enabled
			if (mMCWindowOnly && GetForegroundWindow() != FindWindowA("LWJGL", nullptr))
				continue;

			input::sendClick(mBlockChance, mRightClick);
			input::sendJitter(mJitter);
			clicked = true;
		}

		if (GetAsyncKeyState(mToggleKey))
		{
			if (!wasPressed)
			{
				wasPressed = true;
				mEnabled = !mEnabled;
			}
		}

		if (clicked) // sleep for randomized amount of time if clicking
		{
			preciseSleep(inputmath::cpsToDelay(cps) / 1000);
		}
		else // else, update at same rate as GUI
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(gui::updateDelay));
		}
	}
}