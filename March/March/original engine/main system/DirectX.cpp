#include "DirectX.h"

HRESULT DirectX11::Init(HWND _hwnd)
{
	HRESULT _hr = S_OK;

	_hr = CreateDevice();

	_hr = CreateSwapChain(_hwnd);

	return _hr;
}

void DirectX11::Uninit()
{
	swapchain->SetFullscreenState(false, nullptr);
	swapchain->Release();
	context->Release();
	device->Release();
}

void DirectX11::Present()
{
	swapchain->Present(0, 0);
}


HRESULT DirectX11::CreateDevice()
{
	HRESULT _hr = S_OK;

	UINT _create_device_flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined( DEBUG ) || defined( _DEBUG )
	_create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL _feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};
	UINT _num_feature_levels = ARRAYSIZE(_feature_levels);

	D3D_DRIVER_TYPE _driver_types[] =
	{
		D3D_DRIVER_TYPE_UNKNOWN,
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT _num_driver_types = ARRAYSIZE(_driver_types);

	D3D_FEATURE_LEVEL _feature_level;
	for (D3D_DRIVER_TYPE _driver_type : _driver_types)
	{
		_hr = D3D11CreateDevice(nullptr, _driver_type, nullptr, _create_device_flags, _feature_levels, ARRAYSIZE(_feature_levels), D3D11_SDK_VERSION, device.GetAddressOf(), &_feature_level, context.GetAddressOf());

		if (SUCCEEDED(_hr))
		{
			break;
		}
	}

	return _hr;
}

HRESULT DirectX11::CreateSwapChain(HWND _hwnd)
{
	HRESULT _hr = S_OK;


	DXGI_SWAP_CHAIN_DESC _sd;
	ZeroMemory(&_sd, sizeof(_sd));
	_sd.BufferCount = 1;
	_sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	RECT _rc;
	GetClientRect(_hwnd, &_rc);
	UINT screen_width = _rc.right - _rc.left;
	UINT screen_height = _rc.bottom - _rc.top;
	_sd.BufferDesc.Width = screen_width;
	_sd.BufferDesc.Height = screen_height;

	_sd.BufferDesc.RefreshRate.Numerator = setup.refresh_rate_numerator;
	_sd.BufferDesc.RefreshRate.Denominator = 1;

	_sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

	_sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	_sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	_sd.OutputWindow = _hwnd;

	BOOL _enable_4x_msaa = FALSE;
	UINT _msaa_quality_level;
	device->CheckMultisampleQualityLevels(_sd.BufferDesc.Format, 4, &_msaa_quality_level);
	_sd.SampleDesc.Count = _enable_4x_msaa ? 4 : 1;
	_sd.SampleDesc.Quality = _enable_4x_msaa ? _msaa_quality_level - 1 : 0;

	_sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	_sd.Flags = 0;
	_sd.Windowed = setup.windowed;


	Microsoft::WRL::ComPtr<IDXGIFactory1> _dxgi_factory;
	Microsoft::WRL::ComPtr<IDXGIDevice> _dxgi_device;

	_hr = device.Get()->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(_dxgi_device.GetAddressOf()));

	Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;
	_hr = _dxgi_device->GetAdapter(adapter.GetAddressOf());

	_hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(_dxgi_factory.GetAddressOf()));
	_hr = _dxgi_factory->CreateSwapChain(device.Get(), &_sd, swapchain.GetAddressOf());
	
	return _hr;
}
