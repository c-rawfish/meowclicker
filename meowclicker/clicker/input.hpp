#pragma once

namespace inputmath
{
	float getRandomFloat(float min, float max) noexcept;

	float cpsToDelay(float cps) noexcept;
}

namespace input
{
	const float jitterBase = 0.5F;

	void sendClick(float blockChance, bool rightClick) noexcept;
	void sendJitter(float jitterFactor) noexcept;
	void clickLoop() noexcept;
}