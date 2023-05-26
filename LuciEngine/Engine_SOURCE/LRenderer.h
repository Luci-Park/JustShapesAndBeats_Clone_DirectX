#pragma once
#include "LuciEngine.h"
#include "LGraphicDevice_Dx11.h"

using namespace lu::math;
namespace lu::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	extern Vertex vertexes[];
	extern ID3D11InputLayout* triangleLayout;
	extern ID3D11Buffer* triangleBuffer; //vertex buffer
	extern ID3DBlob* errorBlob;
	//vertex shader
	//shader코드가 blob에저장되어서 옮긴다.
	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVSShader;
	extern ID3DBlob* trianglePSBlob;
	extern ID3D11PixelShader* trianglePSShader;

	void Initialize();
}

