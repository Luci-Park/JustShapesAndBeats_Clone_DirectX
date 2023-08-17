#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name 

#define CBSLOT_TRANSFORM		0
#define CBSLOT_GRID				1
#define CBSLOT_MESHRENDERER		2
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
		End
	};

	//ConstantBuffer : buffers to send to GPU via shader
	enum class eCBType
	{
		Transform,
		Grid,
		MeshRenderer,
		End
	};

	//Sampler : if the image size and target size is different, how will you add or delete the pixels?
	//Minification, Magnification, MipMap
	enum class eSamplerType
	{
		Point, //as pixel = point to point
		Anisotropic, // more smooth.
		End
	};

	// RasterizerState
	// fillmode : how wil you fill the area?
	// cullmode : which parts will you not show?
	// frontcounterclockwise : which is the front and back?
	enum class eRSType 
	{
		SolidBack,//cull back
		SolidFront, // cull front
		SolidNone, // no cull
		WireframeNone, // wireframe + no cull
		End
	};

	enum class eDSType //DepthStencil
	{
		Less,
		Greater,
		NoWrite,
		None,
		End
	};

	enum class eBSType //BendState
	{
		Default,
		AlphaBlend,
		OneOne,
		End
	};

	enum class eRenderingMode
	{
		Opaque,
		CutOut,
		Transparent,
		End,
	};

	enum class eViewType //���ҽ� �� = vertiex, pixel, constant, stream �� ������ ���������� resource view�� ���ؼ� �����Ѵ�.
	{
		None,
		RTV, //Render Target View 
		DSV, //Depth Stencil View
		SRV, //Shader Resource View = ���̴� �ȿ��� �а� ����� ���� ������ ������� ���ϴ� �ڷ�. ��� ���̴� �ܰ迡�� ��� ����
		UAV, // Unordered Access View  = �ȼ� ���̴�, ��� ���̴�, scatter ���� ����.
		End
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

	struct DebugMesh
	{
		enums::eColliderType type;
		math::Vector3 position;
		math::Quaternion rotation;
		math::Vector3 scale;

		math::Color color;

		float radius;
		float duration;
		float time;
	};
}