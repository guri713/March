#pragma once
#include <wrl.h>
#include <d3d11.h>

struct sDirectX11Setup
{
	int refresh_rate_numerator = 60;
	bool windowed = false;
};

class DirectX11
{
private:
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain;

	sDirectX11Setup setup;
public:
	DirectX11(sDirectX11Setup _setup) :setup(_setup) {}

	bool Init(HWND _hwnd);
	void Uninit();
	void Present();

	ID3D11Device** GetDevice() { return device.GetAddressOf(); }
	ID3D11DeviceContext** GetContext() { return context.GetAddressOf(); }
	IDXGISwapChain** GetSwapChain() { return swapchain.GetAddressOf(); }

private:
	HRESULT CreateDevice();
	HRESULT CreateSwapChain(HWND _hwnd);
};
