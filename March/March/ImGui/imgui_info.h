#pragma once

#include <Windows.h>
#include <d3d11.h>

#ifdef _DEBUG
#define USE_IMGUI
#endif 

#ifdef USE_IMGUI
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam);

#endif

class ImGuiManager
{
private :
	ImGuiManager() { is_reset = false; }
	~ImGuiManager() {}
	bool is_reset;
public:

	void Init(HWND _handle, ID3D11Device* _device, ID3D11DeviceContext* _context, float* _screen_size);
	void Update();
	void Render();
	void Uninit();
	void Reset(HWND _handle, ID3D11Device* _device, ID3D11DeviceContext* _context, float* _screen_size);

	void SetFont(const char* _font_name,const float _font_size = 30.0f,const float _scale = 0.6f);

	static ImGuiManager* GetInstance() 
	{
		static ImGuiManager instance;
		return &instance;
	}
};