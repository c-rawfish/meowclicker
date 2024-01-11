#pragma once
#include <random>
#include <Windows.h>

namespace inputmath
{
	int getRandomInt(int min, int maxExclusive);
	float getRandomFloat(float min, float max);

	float cpsToDelay(float cps);
}

namespace input
{
	void sendClick(float blockChance, bool rightClick);
	void sendJitter(float jitterFactor);
	void clickLoop();
}