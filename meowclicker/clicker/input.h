#pragma once
#include <random>
#include <Windows.h>

namespace inputmath
{
	int getRandomInt(int min, int max);
	float getRandomFloat(float min, float max);

	float cpsToDelay(float cps);
}

namespace input
{
	void sendClick(float blockChance);
	void sendJitter(float jitterFactor);
}