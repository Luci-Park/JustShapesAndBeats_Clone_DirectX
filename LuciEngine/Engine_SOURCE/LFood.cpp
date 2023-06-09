#include "LFood.h"
#include "LApplication.h"

extern lu::Application application;
namespace lu
{
	Food::Food()
		: mMesh(nullptr)
		, mShader(nullptr)
		, mConstantBuffer(nullptr)
	{
		mPos.x = (GetRandomInt(0, application.GetWidth()) - (application.GetWidth() * 0.5)) / (application.GetWidth() * 0.5);
		mPos.y = (GetRandomInt(0, application.GetHeight()) - (application.GetHeight() * 0.5)) / (application.GetHeight() * 0.5);
	}
	Food::~Food()
	{
	}
	void Food::Initialize()
	{
		SetVertices();
		LoadBuffer();
		LoadShader();
		SetUpState();
	}
	void Food::Update()
	{
	}
	void Food::LateUpdate()
	{
	}
	void Food::Render()
	{
		mMesh->BindBuffer();
		mShader->Binds();
		GetDevice()->DrawIndexed(mMesh->GetIndexCount(), 0, 0);
	}
	void Food::SetVertices()
	{
		Vector4 color(GetRandomInt(0, 255) / 255.0f, GetRandomInt(0, 255) / 255.0f, GetRandomInt(0, 255) / 255.0f, 1.0f);
		int segments = 30;

		float angleIncrement = std::numbers::pi * 2 / segments;
		float angle = 0.0f;

		mVertices.resize(segments + 1);

		for (int i = 0; i <= segments; i++, angle += angleIncrement)
		{
			float x = mRadius * cos(angle);
			float y = mRadius * sin(angle);

			mVertices[i].pos = Vector3(x, y, 0.0f);
			mVertices[i].color = color;
		}
		mVertices[segments].pos = Vector3::Zero;
		mVertices[segments].color = color;
	}
	void Food::LoadBuffer()
	{
		mMesh = new Mesh();
		mMesh->CreateVertexBuffer(mVertices.data(), mVertices.size());

		int segments = mVertices.size() - 1;
		std::vector<UINT> indices;

		for (int i = 0; i < segments; ++i)
		{
			indices.push_back(segments);
			indices.push_back((i + 1) % segments);
			indices.push_back((i) % segments);
		}
		mMesh->CreateIndexBuffer(indices.data(), indices.size());

		mConstantBuffer = new ConstantBuffer(eCBType::Transform);
		mConstantBuffer->Create(sizeof(Vector4));

		Vector4 pos;
		pos.x = mPos.x;
		pos.y = mPos.y;
		pos.z = 0;
		pos.w = 1.0;
		
		mConstantBuffer->SetData(&pos);
		mConstantBuffer->Bind(eShaderStage::VS);
	}
	void Food::LoadShader()
	{
		mShader = new Shader();
		mShader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		mShader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
	}
	void Food::SetUpState()
	{
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


		GetDevice()->CreateInputLayout(arrLayout, 2, mShader->GetVSCode(), mShader->GetInputLayoutAddressOf());
	}
}