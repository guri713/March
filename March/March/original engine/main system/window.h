#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <cassert>
#include <tchar.h>
#include <sstream>
#include <memory>
#include <wrl.h>

#include "../calculation/vector.h"

enum class e_window_mode
{
	window,
	borderless,
	fullscreen
};

struct sWindowSetup
{
	std::wstring window_name = L"";
	Vector2 window_size = {1920.0f,1080.0f};
	int icon_num = -1;
	e_window_mode window_mode = e_window_mode::window;
};

class Window
{
private:
	HWND hwnd = nullptr;

	sWindowSetup setup;

public:
	Window(sWindowSetup _setup) : setup(_setup) {}

	bool Init(HINSTANCE _instance,INT _cmd_show);

	void Uninit();

	LRESULT CALLBACK HandleMessage(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);

	void SetWindowSize(Vector2 _window_size);

	HWND GetHWND() { return hwnd; }
private:

};

//class Framework
//{
//private:
//	HWND hwnd = nullptr;
//
//
//	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rendertarget;
//	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthstencil;
//
//public:
//	void Initialize(HWND _handle);
//
//	void Render();
//};