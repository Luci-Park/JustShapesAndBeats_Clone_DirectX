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
	};

	extern Vertex vertexes[];
	extern Mesh* mesh;
	extern Shader* shader;
	extern ConstantBuffer* constantBuffer;

	void Initialize();
	void Release();
}

