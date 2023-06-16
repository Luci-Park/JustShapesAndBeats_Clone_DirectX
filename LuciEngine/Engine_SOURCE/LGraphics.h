#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace lu::graphics
{
	enum class eShaderStage
	{
		VS, //Vertex Shader
		HS, //Hull Shader
		DS, //Domain Shader
		GS, //Geometry shader
		PS, //Pixel Shader
		CS, //Compute Shader
		None
	};

	enum class eCBType
	{
		Transform,
		None
	};

	struct GpuBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		D3D11_BUFFER_DESC desc;

		GpuBuffer()
			: buffer(nullptr)
			, desc{}
		{

		}
		virtual ~GpuBuffer() = default;
	};
}