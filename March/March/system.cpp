#include "window.h"
#include "DirectX.h"
#include "system.h"
#include "ImGui/imgui_info.h"

void System::Startup(HINSTANCE _instance)
{
	sWindowSetup _window_setup;
	_window_setup.window_name = L"demo";

	window = new Window(_window_setup);
	if (window->Init(_instance) == S_FALSE)
		assert(1 && "Window creation failed.");
	HWND _hwnd = window->GetHWND();


	sDirectX11Setup directX11_setup;
	directX11_setup.refresh_rate_numerator = 60;
	directX11_setup.windowed = true;

	directX11 = new DirectX11(directX11_setup);
	if (directX11->Init(_hwnd) == S_FALSE)
		assert(1 && "DirectX initialization failed.");


	ImGuiManager::GetInstance()->Init(_hwnd, *directX11->GetDevice(), *directX11->GetContext(), &_window_setup.window_size.x);

	UpdateWindow(_hwnd);
}

bool System::Run()
{
	MSG msg;
	while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			return false;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	ImGuiManager::GetInstance()->Update();
	return true;
}

void System::Closing()
{
	ImGuiManager::GetInstance()->Uninit();
	delete directX11;
	delete window;
}
