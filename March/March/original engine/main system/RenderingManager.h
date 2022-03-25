#pragma once

#include <memory>
#include <wrl.h>
#include <d3d11.h>
#include <vector>
#include <wincodec.h>
#include "../calculation/vector.h"
#include "shaders.h"

class RenderingManager
{
public:
	enum class e_type
	{
		vertex,
		pixel,
		compute,
		geometry,
		rasterize,
		depth,
		sampler
	};

private:
	ID3D11Buffer* vertex_buffer;
	struct s_vertex
	{
		DirectX::XMFLOAT4 position;
		DirectX::XMFLOAT2 texcoord;
	};
	ID3D11Device* device;
	ID3D11DeviceContext* context;
	Vector2 screen_size;

	VertexShader vs[static_cast<int>(e_vertx_type::end)];
	PixelShader ps[static_cast<int>(e_pixel_type::end)];
	ComputeShader cs[static_cast<int>(e_compute_type::end)];
	GeometryShader gs[static_cast<int>(e_geometry_type::end)];
	RasterizerState rs[static_cast<int>(e_rasterizer_type::end)];
	DepthStensilState ds[static_cast<int>(e_depth_type::end)];
	SamplerState ss[static_cast<int>(e_sample_type::end)];
	ID3D11BlendState* bs[static_cast<int>(e_blend_type::end)];
	RenderTarget* rt[static_cast<int>(e_rendertraget_type::end)];
	DepthStencil* dsv[static_cast<int>(e_depthstencilview_type::end)];

	ID3D11Texture2D* iTexture[18] = { nullptr };
	ID3D11UnorderedAccessView* comOut[18] = { nullptr };
	ID3D11ShaderResourceView* UAVTex[18] = { nullptr };

private:
	RenderingManager();
	~RenderingManager();
public:
	void Init();
	void Uninit();

	
	static RenderingManager* GetInstance()
	{
		static RenderingManager _instance;
		return &_instance;
		
	}
};