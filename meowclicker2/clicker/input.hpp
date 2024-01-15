#pragma once

#include "clicker.hpp"

#include <vector>
#include <Windows.h>

namespace input
{
	inline constexpr float jitterBase = 0.5F;

	void sendClick(HWND window, bool rightClick) noexcept;
	void sendJitter(float jitter) noexcept;
}