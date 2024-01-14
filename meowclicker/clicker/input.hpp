#pragma once
#include <vector>
#include "gui.hpp"
#include "config.hpp"

void preciseSleep(double seconds);

namespace inputmath
{
	float getRandomFloat(float min, float max) noexcept;

	float cpsToDelay(float cps) noexcept;
}

namespace input
{
	inline constexpr float jitterBase = 0.5F;

	void sendClick(float blockChance, bool rightClick) noexcept;
	void sendJitter(float jitterFactor) noexcept;

	void clickLoopSetup(const std::vector<Clicker> &clickers);
}