#include "LRenderer.h"
namespace lu::renderer
{
	Vertex vertexes[3] = {};

	//Input Layout = vertex info
	ID3D11InputLayout* triangleLayout = nullptr;

	//Vertex Buffer
	ID3D11Buffer* triangleBuffer = nullptr;

	//error blob => returns error from shader, because the compiler doesn't
	ID3DBlob* errorBlob = nullptr;

	//VertexShader Code -> Binary Code, hold in blob
	ID3DBlob* triangleVSBlob = nullptr;

	//vertex shader
	ID3D11VertexShader* triangleVSShader = nullptr;

	//pixel shader code -> binary code
	ID3DBlob* trianglePSBlob = nullptr;

	//Pixel shader code ->Binary code
	ID3D11PixelShader* trianglePSShader = nullptr;

	void SetupState()
	{

	}

	void LoadBuffer()
	{
		D3D11_BUFFER_DESC triangleDesc = {};
		triangleDesc.Usage = D3D11_USAGE_DYNAMIC;
		triangleDesc.ByteWidth = sizeof(Vertex) * 3;
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = vertexes;
		lu::graphics::GetDevice()->CreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);
	}

	void LoadShader()
	{
		lu::graphics::GetDevice()->CreateShader();
	}

	void Initialize()
	{
		vertexes[0].pos = Vector3(0.0f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[1].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		SetupState();
		LoadBuffer();
		LoadShader();
	}
}