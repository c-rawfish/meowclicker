#pragma once

class Clicker
{
private:
	bool mEnabled;
	int mKey;
	int mToggleKey;
	bool mRightClick;
	bool mMCWindowOnly;
	float mMinCPS;
	float mMaxCPS;
	float mJitter;
	float mBlockChance;

public:
	Clicker(int key, int toggleKey, bool rightClick, float blockChance);

	bool getEnabled() const;
	int getKey() const;
	int getToggleKey() const;
	bool getRightClick() const;
	bool getMCWindowOnly() const;
	float getMinCPS() const;
	float getMaxCPS() const;
	float getJitter() const;
	float getBlockChance() const;

	bool* getEnabledPtr();
	int* getKeyPtr();
	int* getToggleKeyPtr();
	bool* getRightClickPtr();
	bool* getMCWindowOnlyPtr();
	float* getMinCPSPtr();
	float* getMaxCPSPtr();
	float* getJitterPtr();
	float* getBlockChancePtr();

	void setEnabled(bool enabled);
	void setKey(int key);
	void setToggleKey(int toggleKey);
	void setRightClick(bool rightClick);
	void setMCWindowOnly(bool mcWindowOnly);
	void setMinCPS(float minCPS);
	void setMaxCPS(float maxCPS);
	void setJitter(float jitter);
	void setBlockChance(float blockChance);

	void clickLoop();
};