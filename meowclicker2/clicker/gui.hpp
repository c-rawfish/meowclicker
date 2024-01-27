#pragma once

#include "clicker.hpp"

#include <d3d9.h>
#include <string>
#include <format>

namespace gui
{
	inline constexpr const char* name  = "meowclicker";
	inline constexpr float version     = 1.3.1;
	inline const     std::string title = std::format("{} v{:.2}", name, version);

	inline constexpr int  WIDTH       = 500;
	inline constexpr int  HEIGHT      = 300;
	inline constexpr long updateDelay = 16L;

	inline bool isRunning = true;

	inline HWND       window      = nullptr;
	inline WNDCLASSEX windowClass = { };

	inline POINTS position = { };

	inline PDIRECT3D9            d3d               = nullptr;
	inline LPDIRECT3DDEVICE9     device            = nullptr;
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
	void render(Clicker* leftClicker, Clicker* rightClicker) noexcept;
}
