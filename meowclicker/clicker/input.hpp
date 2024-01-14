#pragma once
#include <vector>
#include "gui.hpp"

namespace inputmath
{
	float getRandomFloat(float min, float max) noexcept;

	float cpsToDelay(float cps) noexcept;
}

namespace input
{
	inline constexpr float jitterBase = 0.5F;

	void sendClick(float blockChance, bool rightClick) noexcept;
	void sendJitter(const float jitterFactor) noexcept;
	void clickLoop(const std::vector<config::Clicker> &clickers) noexcept;
}