#pragma once
#include <d3d9.h>

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
	constexpr int WIDTH = 350;
	constexpr int HEIGHT = 250;

	inline bool isRunning = true;

	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = { };

	inline POINTS position = { };

	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = { };

	void CreateHWindow(const char* windowName) noexcept;
	void DestroyHWindow() noexcept;

	bool CreateDevice() noexcept;
	void ResetDevice() noexcept;
	void DestroyDevice() noexcept;

	void CreateImGui() noexcept;
	void DestroyImGui() noexcept;

	void BeginRender() noexcept;
	void EndRender() noexcept;
	void Render() noexcept;
}