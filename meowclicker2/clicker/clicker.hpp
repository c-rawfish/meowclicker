#pragma once

class Clicker
{
private:
	bool       mEnabled;
	bool       mMCWindowOnly;
	const int  mKey;
	const int  mToggleKey;
	const bool mRightClick;
	float      mMinCPS;
	float      mMaxCPS;
	float      mJitter;
	float      mBlockChance;
public:
	Clicker(int key, int toggleKey, bool rightClick);

	bool* getEnabledPtr();
	bool* getMCWindowOnlyPtr();
	float* getMinCPSPtr();
	float* getMaxCPSPtr();
	float* getJitterPtr();
	float* getBlockChancePtr();

	// const values, never need a pointer returned (just the value for checks)
	int getKey() const;
	int getToggleKey() const;
	bool getRightClick() const;

	// only value ever being modified directly
	void setMaxCPS(float cps);

	void startClickLoop();
};

