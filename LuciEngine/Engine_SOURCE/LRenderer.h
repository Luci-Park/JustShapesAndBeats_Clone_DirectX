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

	extern Vertex vertexes[];
	extern ConstantBuffer* constantBuffer[(UINT)eCBType::End];

	void Initialize();
	void Release();
}

