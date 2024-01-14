#include "input.hpp"
#include "gui.hpp"

#include <thread>
#include <random>
#include <Windows.h>
#include <chrono>
#include <cmath>

void preciseSleep(double seconds) {
	using namespace std;
	using namespace std::chrono;

	static double estimate = 5e-3;
	static double mean = 5e-3;
	static double m2 = 0;
	static int64_t count = 1;

	while (seconds > estimate) {
		auto start = high_resolution_clock::now();
		this_thread::sleep_for(milliseconds(1));
		auto end = high_resolution_clock::now();

		double observed = (end - start).count() / 1e9;
		seconds -= observed;

		++count;
		double delta = observed - mean;
		mean += delta / count;
		m2 += delta * (observed - mean);
		double stddev = sqrt(m2 / (count - 1));
		estimate = mean + stddev;
	}

	// spin lock
	auto start = high_resolution_clock::now();
	while ((high_resolution_clock::now() - start).count() / 1e9 < seconds);
}

namespace inputmath
{
	float getRandomFloat(float min, float max) noexcept
	{
		std::random_device                  rand_dev;
		std::mt19937                        gen(rand_dev());
		std::uniform_real_distribution<float>  dist(min, max);

		return dist(gen);
	}

	float cpsToDelay(float cps) noexcept
	{
		return 1000 / cps;
	}
}

namespace input
{
	POINT mousePos{ 0, 0 };
	HWND foreground{ GetForegroundWindow() };

	void sendClick(float blockChance, bool rightClick) noexcept
	{
		GetCursorPos(&mousePos);
		foreground = GetForegroundWindow();

		LPARAM mouseParam = MAKELPARAM(mousePos.x, mousePos.y);
		
		PostMessageA(foreground, rightClick ? WM_RBUTTONDOWN : WM_LBUTTONDOWN, 0, mouseParam);
		if (!rightClick && inputmath::getRandomFloat(0, 100) < blockChance)
		{
			PostMessageA(foreground, WM_RBUTTONDOWN, 0, mouseParam);
			PostMessageA(foreground, WM_RBUTTONUP, 0, mouseParam);
		}
		PostMessageA(foreground, rightClick ? WM_RBUTTONUP : WM_LBUTTONUP, 0, mouseParam);
	}

	void sendJitter(float jitterFactor) noexcept
	{
		float jitterX = inputmath::getRandomFloat(-jitterBase, jitterBase) * jitterFactor;
		float jitterY = inputmath::getRandomFloat(-jitterBase, jitterBase) * jitterFactor;

		mousePos.x += jitterX;
		mousePos.y += jitterY;

		SetCursorPos(mousePos.x, mousePos.y);
	}

	void clickLoopSetup(const std::vector<Clicker> &clickers)
	{
		for (auto &clicker : clickers)
		{
			std::jthread clickThread(&Clicker::clickLoop, clicker);
			clickThread.detach();
		}
	}
}