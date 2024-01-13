#pragma once
#include <vector>
#include "gui.hpp"

namespace inputmath
{
	float getRandomFloat(const float min, const float max) noexcept;

	float cpsToDelay(const float cps) noexcept;
}

namespace input
{
	inline constexpr float jitterBase = 0.5F;

	void sendClick(const float blockChance, const bool rightClick) noexcept;
	void sendJitter(const float jitterFactor) noexcept;
	void clickLoop(std::vector<config::Clicker>* clickers) noexcept;
}