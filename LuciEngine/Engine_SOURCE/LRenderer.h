#pragma once
#include "LuciEngine.h"
#include "LGraphicDevice_Dx11.h"
#include "LShader.h"
#include "LMesh.h"
#include "LConstantBuffer.h"

using namespace lu::math;
namespace lu::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix mWorld;
		Matrix mView;
		Matrix mProjection;
	};

	extern Vertex vertexes[];
	extern ConstantBuffer* constantBuffer[(UINT)eCBType::End];
	
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState>samplerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState>rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState>depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	void Initialize();
	void Release();
}

