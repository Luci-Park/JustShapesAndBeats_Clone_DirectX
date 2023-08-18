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
#define CBSLOT_PARTICLESYSTEM	3
#define	CBSLOT_NOISE			4
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
		ParticleSystem,
		Noise,
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

	enum class eResourceViewType
	{
		None,
		//RTV, //render target view = provides write access to a texture or a portion of a texture. => specify the final output. used for color buffers
		//DSV, // depth stencil view = provides read-write access to depth and stencil buffers of a texture. stores information about the depths of each pixel in the scene
		SRV, // shader resource view = a readonly access to a texture, can be used to access texture data for calcualations, sampling, and other operations. color maps, normal maps, height maps etc.
		UAV,// unordered access view = provides a read-write access to a texture or a portion of a texture within a compute shader. used for general-purpose computing tasks. good for compute shaders.
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

	struct Particle
	{
		math::Vector4 position;
		math::Vector4 direction;

		float endTime;
		float time;
		float speed;
		UINT active;
	};

	struct ParticleShared
	{
		UINT sharedActiveCount;
	};
}