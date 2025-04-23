#pragma once

#include <d3d11.h>
#include <dwmapi.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>

namespace Render
{
	constexpr int Width = 1920, Height = 1080;

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HRESULT InitDirectX();

	WPARAM RenderLoop(void (*func)());
}
