#include "LRenderer.h"
namespace lu::renderer
{
	Vertex vertexes[3] = {};

	//Input Layout = vertex info
	ID3D11InputLayout* triangleLayout = nullptr;

	//Vertex Buffer
	ID3D11Buffer* triangleBuffer = nullptr;
	ID3D11Buffer* triangleIdxBuffer = nullptr;
	ID3D11Buffer* triangleConstantBuffer = nullptr;

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
		triangleDesc.ByteWidth = sizeof(Vertex) * 3; // 점 3개
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = vertexes;
		lu::graphics::GetDevice()->CreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);

		std::vector<UINT>indices = {};
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		D3D11_BUFFER_DESC triangleIdxDesc = {};
		triangleIdxDesc.ByteWidth = sizeof(UINT) * indices.size();
		triangleIdxDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		triangleIdxDesc.Usage = D3D11_USAGE_DEFAULT;
		triangleIdxDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA triangleIdxData = {};
		triangleIdxData.pSysMem = indices.data();
		lu::graphics::GetDevice()->CreateBuffer(&triangleIdxBuffer, &triangleIdxDesc, &triangleIdxData);

		//Constant Buffer
		D3D11_BUFFER_DESC triangleCSDesc = {};
		triangleCSDesc.ByteWidth = sizeof(Vector4);
		triangleCSDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		triangleCSDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleCSDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		lu::graphics::GetDevice()->CreateBuffer(&triangleConstantBuffer, &triangleCSDesc, nullptr);

		Vector4 pos(0.3f, 0.0f, 0.0f, 1.0f);
		lu::graphics::GetDevice()->SetConstantBuffer(triangleConstantBuffer, &pos, sizeof(Vector4));
		lu::graphics::GetDevice()->BindConstantBuffer(eShaderStage::VS, eCBType::Transform, triangleConstantBuffer);
	}

	void LoadShader()
	{
		lu::graphics::GetDevice()->CreateShader();
	}

	void Initialize()
	{
		//vertex정보 생성
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
	void Release()
	{
		if (triangleLayout != nullptr)
			triangleLayout->Release();

		if (triangleBuffer != nullptr)
			triangleBuffer->Release();

		if (triangleIdxBuffer != nullptr)
			triangleIdxBuffer->Release();

		if (triangleConstantBuffer != nullptr)
			triangleConstantBuffer->Release();

		if (errorBlob != nullptr)
			errorBlob->Release();

		if (triangleVSBlob != nullptr)
			triangleVSBlob->Release();

		if (triangleVSShader != nullptr)
			triangleVSShader->Release();

		if (trianglePSBlob != nullptr)
			trianglePSBlob->Release();

		if (trianglePSShader != nullptr)
			trianglePSShader->Release();
	}
}