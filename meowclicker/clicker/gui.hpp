#pragma once
#include <d3d9.h>
#include <string>
#include <format>

namespace config
{
	inline bool enabled = false;
	inline bool rightClick = false;
	inline bool mcWindow = false;
	inline float minCPS = 12;
	inline float maxCPS = 17;
	inline float jitter = 0;
	inline float blockChance = 0;
}

// skidded from cazz
namespace gui
{
	inline constexpr std::string name = "meowclicker";
	inline constexpr std::string version = "v1.2";
	inline const std::string title = std::format("{} {}", name, version).c_str();

	constexpr int updateDelay = 16;

	constexpr int WIDTH = 350;
	constexpr int HEIGHT = 250;

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
	void render() noexcept;
}