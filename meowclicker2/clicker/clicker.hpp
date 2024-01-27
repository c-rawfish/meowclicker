#pragma once

#include <Windows.h>

class Clicker
{
public:
	Clicker(bool rightClick, int toggleKey);

	bool mEnabled;
	bool mMcWindowOnly;
	const bool mRightClick;
	const int mMouseKey;
	const int mToggleKey;
	float mMinCps;
	float mMaxCps;
	float mJitter;

private:
	void sendClick(LPARAM mouseParam);
	void clickLoop();
};

