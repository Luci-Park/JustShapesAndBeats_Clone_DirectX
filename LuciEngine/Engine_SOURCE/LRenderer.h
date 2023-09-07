#pragma once
#include "LuciEngine.h"
#include "LGraphicDevice_Dx11.h"
#include "LShader.h"
#include "LMesh.h"
#include "LConstantBuffer.h"
#include "LCamera.h"

#define TEXSLOT_NOISE	15
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
		Matrix world;
		Matrix view;
		Matrix projection;
	};

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 cameraPosition;
		Vector2 cameraScale;
		Vector2 resolution;
	};
	CBUFFER(MeshRendererCB, CBSLOT_MESHRENDERER)
	{
		lu::math::Color tint;
		lu::math::Color color;
		Vector2 Flip;
		float interpolation; // 0 uses original, 1 uses Color;
		UINT padding;
	};

	CBUFFER(ParticleSystemCB, CBSLOT_PARTICLESYSTEM)
	{
		lu::math::Color startTint;
		lu::math::Color endTint;
		
		float	lifeTime;
		float	elapsedTime;
		float	deltaTime;
		float	gravityRate;
		
		float   particleAngle1;
		float   particleAngle2;
		float startRot;
		float rotSpeed;

		float startSize;
		float endSize;
		float startSpeed;
		float endSpeed;
		
		UINT elementCount;
		UINT isParticleInWorldSpace;
		Vector2 padd;
	};

	CBUFFER(NoiseCB, CBSLOT_NOISE)
	{
		Vector4 size;
	};

	extern ConstantBuffer* constantBuffer[(UINT)eCBType::End];
	
	extern Microsoft::WRL::ComPtr<ID3D11SamplerState>samplerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState>rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState>depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];
	
	//extern lu::Camera* mainCamera;
	//extern std::vector<lu::Camera*> cameras;
	extern std::vector<DebugMesh>debugMeshes;

	void Initialize();
	void Render();
	void Release();

	void PushDebugMeshAttribute(DebugMesh mesh);
}

