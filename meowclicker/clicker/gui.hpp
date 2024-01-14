#pragma once
#include <d3d9.h>
#include <string>
#include <format>
#include <vector>

namespace config
{
	inline constexpr float kMaxRightCps = 50;
	inline constexpr float kMaxLeftCps = 20;

	struct Clicker
	{
		bool enabled;
		int key;
		int toggleKey;
		bool rightClick;
		bool mcWindow;
		float minCPS;
		float maxCPS;
		float jitter;
		float blockChance;
		/*bool enabled = false;
		int key = VK_LBUTTON;
		int toggleKey = VK_F6;
		bool rightClick = false;
		bool mcWindow = false;
		float minCPS = 12;
		float maxCPS = 17;
		float jitter = 0;
		float blockChance = 0;*/
	};
}

// skidded from cazz
namespace gui
{
	inline constexpr const char *name = "meowclicker";
	inline constexpr float version = 1.3;
	inline const std::string title = std::format("{} v{:.2}", name, version);

	inline constexpr int updateDelay = 16;

	constexpr int WIDTH = 350;
	constexpr int HEIGHT = 275;

	inline bool isRunning = true;

	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = { };

	inline POINTS position = { };

	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = { };

	void createHWindow(const char* windowName) noexcept;
	void destroyHWindow() noexcept;

	bool createDevice() noexcept;
	void resetDevice() noexcept;
	void destroyDevice() noexcept;

	void createImGui() noexcept;
	void destroyImGui() noexcept;

	void beginRender() noexcept;
	void endRender() noexcept;
	void render(std::vector<config::Clicker>* clickers) noexcept;
}