#pragma once
#include <d3d11.h>
#include <string>
#include <DirectXTex.h>
#include "ResourceManager.h"

class VertexShader
{
public:
	ID3D11VertexShader* shader = nullptr;
	ID3D11InputLayout* input = nullptr;
	std::string name = std::string();
	int index = 0;

	bool Load(ID3D11Device* _device, const char* _file_name, D3D11_INPUT_ELEMENT_DESC* _desc, const int _num_e, const int _index)
	{
		index = _index;
		name = _file_name;
		size_t start = name.find_last_of("/") + 1, end = name.find_last_of(".") - start;
		name = name.substr(start, end);
		return ResourceManager::LoadVertexShader(_device, _file_name, _desc, _num_e, &shader, &input);
	}

	void Unload()
	{
		if (shader != nullptr)
		{
			ResourceManager::Release(shader, ResourceManager::e_resource_kind::Vertex);
			shader = nullptr;
			input = nullptr;
		}
	}
};

class PixelShader
{
public:
	ID3D11PixelShader* shader = nullptr;
	std::string name = std::string();
	int index = 0;
	bool Load(ID3D11Device* _device, const char* _file_name, const int _index)
	{
		index = _index;
		name = _file_name;
		size_t start = name.find_last_of("/") + 1, end = name.find_last_of(".") - start;
		name = name.substr(start, end);
		return ResourceManager::LoadShader(_device, _file_name, &shader,ResourceManager::e_resource_kind::Pixel);
	}

	void Unload()
	{
		ResourceManager::Release(shader, ResourceManager::e_resource_kind::Pixel);
		shader = nullptr;
	}
};

class ComputeShader
{
public:
	ID3D11ComputeShader* shader = nullptr;
	std::string name = std::string();
	int index = 0;
	bool Load(ID3D11Device* _device, const char* _file_name, const int _index)
	{
		index = _index;
		name = _file_name;
		size_t start = name.find_last_of("/") + 1, end = name.find_last_of(".") - start;
		name = name.substr(start, end);
		return ResourceManager::LoadShader(_device, _file_name, &shader, ResourceManager::e_resource_kind::Compute);
	}

	void Unload()
	{
		ResourceManager::Release(shader, ResourceManager::e_resource_kind::Compute);
		shader = nullptr;
	}

};

class GeometryShader
{
public:
	ID3D11GeometryShader* shader = nullptr;
	std::string name = std::string();
	int index = 0;
	bool Load(ID3D11Device* _device, const char* _file_name, const int _index)
	{
		index = _index;
		name = _file_name;
		size_t start = name.find_last_of("/") + 1, end = name.find_last_of(".") - start;
		name = name.substr(start, end);
		return ResourceManager::LoadShader(_device, _file_name, &shader,ResourceManager::e_resource_kind::Geometry);
	}

	void Unload()
	{
		ResourceManager::Release(shader,ResourceManager::e_resource_kind::Geometry);
		shader = nullptr;
	}
};

class RasterizerState
{
public:
	ID3D11RasterizerState* rasterizer_state = nullptr;
	std::string name = std::string();
	int index = 0;

	bool Create(ID3D11Device* _device, D3D11_RASTERIZER_DESC _desc, const char* _name, const int _index)
	{
		index = _index;
		name = _name;
		HRESULT hr = _device->CreateRasterizerState(&_desc, &rasterizer_state);
		if (hr == S_OK)return true;
		return false;
	}

	void Unload()
	{
		rasterizer_state->Release();
		rasterizer_state = nullptr;
	}

};

class DepthStensilState
{
public:
	ID3D11DepthStencilState* depth_stencil_state = nullptr;
	std::string name = std::string();
	int index = 0;

	bool Create(ID3D11Device* _device, D3D11_DEPTH_STENCIL_DESC _desc, const char* _name, const int _index)
	{
		index = _index;
		name = _name;
		HRESULT hr = _device->CreateDepthStencilState(&_desc, &depth_stencil_state);
		if (hr == S_OK)return true;
		return false;
	}

	void Unload()
	{
		depth_stencil_state->Release();
		depth_stencil_state = nullptr;
	}
};

class SamplerState
{
public:
	ID3D11SamplerState* sampler_state = nullptr;
	std::string name = std::string();
	int index = 0;
	bool Create(ID3D11Device* _device, D3D11_SAMPLER_DESC _desc, const char* _name, const int _index)
	{
		index = _index;
		name = _name;
		HRESULT hr = _device->CreateSamplerState(&_desc, &sampler_state);
		if (hr == S_OK)return true;
		return false;
	}

	void Unload()
	{
		sampler_state->Release();
		sampler_state = nullptr;
	}
};
