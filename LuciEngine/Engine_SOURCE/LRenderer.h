#pragma once
#include "LuciEngine.h"
#include "LGraphicDevice_Dx11.h"
#include "LShader.h"
#include "LMesh.h"
#include "LConstantBuffer.h"
#include "LCamera.h"

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

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 CameraPosition;
		Vector2 CameraScale;
		Vector2 Resolution;
	};
	CBUFFER(MaterialCB, CBSLOT_MATERIAL)
	{
		lu::math::Color Color;
	};

	extern ConstantBuffer* constantBuffer[(UINT)eCBType::End];
	
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState>samplerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState>rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState>depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];
	
	extern lu::Camera* mainCamera;
	extern std::vector<lu::Camera*> cameras;
	extern std::vector<DebugMesh>debugMeshes;

	void Initialize();
	void Render();
	void Release();

	void PushDebugMeshAttribute(DebugMesh mesh);
}

