#include "LRenderer.h"
namespace lu::renderer
{
	std::vector<Vertex> vertices = {};
	Mesh* mesh = nullptr;
	Shader* shader = nullptr;
	ConstantBuffer* constantBuffer = nullptr;

	void SetupState()
	{
		// Input layout 정점 구조 정보를 넘겨줘야한다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;


		GetDevice()->CreateInputLayout(arrLayout, 2	, shader->GetVSCode(), shader->GetInputLayoutAddressOf());
	}

	void LoadBuffer()
	{
		// Vertex Buffer
		mesh = new Mesh();
		mesh->CreateVertexBuffer(vertices.data(), vertices.size());

		int segments = vertices.size() - 1;
		std::vector<UINT> indices;

		for (int i = 0; i < segments; ++i)
		{
			indices.push_back(segments);
			indices.push_back((i + 1) % segments);
			indices.push_back((i) % segments);
		}
		mesh->CreateIndexBuffer(indices.data(), indices.size());

		// Constant Buffer
		constantBuffer = new ConstantBuffer(eCBType::Transform);
		constantBuffer->Create(sizeof(ConstData));
	}

	void LoadShader()
	{
		shader = new Shader();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
	}

	void Initialize()
	{
		Vector4 color(GetRandomInt(0, 255) / 255.0f, GetRandomInt(0, 255) / 255.0f, GetRandomInt(0, 255) / 255.0f, 1.0f);
		int segments = 30;

		float angleIncrement = std::numbers::pi * 2 / segments;
		float angle = 0.0f;

		vertices.resize(segments + 1);


		for (int i = 0; i <= segments; i++, angle += angleIncrement)
		{
			float x = cos(angle);
			float y = sin(angle);

			vertices[i].pos = Vector3(x, y, 0.0f);
			vertices[i].color = color;
		}
		vertices[segments].pos = Vector3::Zero;
		vertices[segments].color = color;

		LoadBuffer();
		LoadShader();
		SetupState();
	}
	void Release()
	{
		delete mesh;
		delete shader;
		delete constantBuffer;
	}
}