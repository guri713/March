#include "window.h"
#include "../ImGui/imgui_info.h"

///<summary>
///callback関数(windows側でアプリが受け取った信号で動作する箇所)
///</summary>
LRESULT CALLBACK fnWndProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	Window* f = reinterpret_cast<Window*>(GetWindowLongPtr(_hwnd, GWLP_USERDATA));
	return f ? f->HandleMessage(_hwnd, _msg, _wparam, _lparam) : DefWindowProc(_hwnd, _msg, _wparam, _lparam);
}

//void Framework::Initialize(HWND _handle)
//{
//	// Create Render Target View
//	D3D11_TEXTURE2D_DESC back_buffer_desc;
//	{
//
//		Microsoft::WRL::ComPtr<ID3D11Texture2D> back_buffer;
//		hr = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(back_buffer.GetAddressOf()));
//
//		hr = device->CreateRenderTargetView(back_buffer.Get(), NULL, rendertarget.GetAddressOf());
//
//		back_buffer->GetDesc(&back_buffer_desc);
//	}
//	// Create Depth Stencil View
//	D3D11_TEXTURE2D_DESC depth_stencil_buffer_desc = back_buffer_desc;
//	{
//		Microsoft::WRL::ComPtr<ID3D11Texture2D> depth_stencil_buffer;
//		depth_stencil_buffer_desc.MipLevels = 1;
//		depth_stencil_buffer_desc.ArraySize = 1;
//		depth_stencil_buffer_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;	//DXGI_FORMAT_D32_FLOAT
//		depth_stencil_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
//		depth_stencil_buffer_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
//		depth_stencil_buffer_desc.CPUAccessFlags = 0;
//		depth_stencil_buffer_desc.MiscFlags = 0;
//		hr = device->CreateTexture2D(&depth_stencil_buffer_desc, NULL, depth_stencil_buffer.GetAddressOf());
//
//		D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
//		depth_stencil_view_desc.Format = depth_stencil_buffer_desc.Format;
//		depth_stencil_view_desc.ViewDimension = enable_4x_msaa ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
//		depth_stencil_view_desc.Flags = 0;
//		depth_stencil_view_desc.Texture2D.MipSlice = 0;
//		hr = device->CreateDepthStencilView(depth_stencil_buffer.Get(), &depth_stencil_view_desc, depthstencil.GetAddressOf());
//	}
//
//	D3D11_VIEWPORT viewport = {};
//	viewport.TopLeftX = 0;
//	viewport.TopLeftY = 0;
//	viewport.Width = static_cast<FLOAT>(screen_width);
//	viewport.Height = static_cast<FLOAT>(screen_height);
//	viewport.MinDepth = 0.0f;
//	viewport.MaxDepth = 1.0f;
//	device_context->RSSetViewports(1, &viewport);
//}
//
//void Framework::Render()
//{
//	HRESULT hr = S_OK;
//
//	FLOAT color[] = { 0.2f, 0.2f, 0.2f, 1.0f };
//	device_context->ClearRenderTargetView(rendertarget.Get(), color);
//	device_context->ClearDepthStencilView(depthstencil.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
//	device_context->OMSetRenderTargets(1, rendertarget.GetAddressOf(), depthstencil.Get());
//
//	swapchain->Present(0, 0);
//}

bool Window::Init(HINSTANCE _instance, INT _cmd_show)
{
	//デバッグ時に出力にエラー出力が出るようにする
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	WNDCLASSEX _wcex;
	_wcex.cbSize = sizeof(WNDCLASSEX);
	_wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	_wcex.lpfnWndProc = fnWndProc;
	_wcex.cbClsExtra = 0;
	_wcex.cbWndExtra = 0;
	_wcex.hInstance = _instance;
	_wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	_wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	_wcex.lpszMenuName = NULL;
	_wcex.lpszClassName = setup.window_name.c_str();

	//アイコンの設定
	if (setup.icon_num != -1)
	{
		_wcex.hIcon = LoadIcon(_instance, MAKEINTRESOURCE(setup.icon_num));
		_wcex.hIconSm = LoadIcon(_instance, MAKEINTRESOURCE(setup.icon_num));
	}
	else
	{
		_wcex.hIcon = NULL;
		_wcex.hIconSm = 0;
	}
	RegisterClassEx(&_wcex);

	RECT rc = { 0, 0, setup.window_size.x, setup.window_size.y };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウの位置を算出
	DirectX::XMFLOAT2 _window_pos = { (GetSystemMetrics(SM_CXSCREEN) - setup.window_size.x) / 2.0f,(GetSystemMetrics(SM_CYSCREEN) - setup.window_size.y) / 2.0f };

	//ウインドウの生成
	hwnd = CreateWindow(setup.window_name.c_str(), setup.window_name.c_str(), (setup.window_mode == e_window_mode::window ? (WS_OVERLAPPEDWINDOW /*^ WS_MAXIMIZEBOX */ ^ WS_THICKFRAME | WS_VISIBLE) : (WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP)), CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, _instance, NULL);

	//ウインドウを最前面に描画
	return ShowWindow(hwnd, _cmd_show);
}

void Window::Uninit()
{
	UnregisterClass(setup.window_name.c_str(), GetModuleHandle(NULL));
}

LRESULT Window::HandleMessage(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
#ifdef USE_IMGUI
	if (ImGui_ImplWin32_WndProcHandler(_hwnd, _msg, _wparam, _lparam))
		return 1;
#endif

	switch (_msg)
	{
	case WM_DESTROY:
		//ウインドウが破棄されるとき
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:

	case WM_ACTIVATEAPP:
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		//DirectX::Mouse::ProcessMessage(_msg, _w_param, _l_param);
		//DirectX::Keyboard::ProcessMessage(_msg, _w_param, _l_param);
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(_hwnd, &ps);
		EndPaint(_hwnd, &ps);
		break;
	}
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		//DirectX::Keyboard::ProcessMessage(_msg, _w_param, _l_param);
		break;

	default:

		return DefWindowProc(_hwnd, _msg, _wparam, _lparam);
	}
	return 0;
}

void Window::SetWindowSize(Vector2 _window_size)
{
	DirectX::XMFLOAT2 _window_pos = { (GetSystemMetrics(SM_CXSCREEN) - _window_size.x) / 2.0f,(GetSystemMetrics(SM_CYSCREEN) - _window_size.y) / 2.0f };

	SetWindowPos(hwnd, HWND_TOP, _window_pos.x, _window_pos.y, _window_size.x, _window_size.y, SWP_SHOWWINDOW);

	setup.window_size = _window_size;
}
