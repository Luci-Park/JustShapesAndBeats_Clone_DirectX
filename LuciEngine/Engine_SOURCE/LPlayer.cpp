#include "LPlayer.h"
#include "LInput.h"
#include "LTime.h"
namespace lu
{
	Player::Player()
		: mMesh(nullptr)
		, mShader(nullptr)
		, mConstantBuffer(nullptr)
		, mPos(Vector2::Zero)
	{
	}
	Player::~Player()
	{
		delete mMesh;
		delete mShader;
		delete mConstantBuffer;
	}
	void Player::Initialize()
	{
		SetVertices();
		LoadBuffer();
		LoadShader();
		SetUpState();
	}
	void Player::Update()
	{
		float moveSpeed = 1.0f;
		Vector2 dir = GetInput();
		mPos += dir * moveSpeed * Time::DeltaTime();

		Vector4 pos;
		pos.x = mPos.x;
		pos.y = mPos.y;
		pos.z = 0;
		pos.w = 1.0;
		mConstantBuffer->SetData(&pos);
		mConstantBuffer->Bind(eShaderStage::VS);
	}
	void Player::LateUpdate()
	{
	}
	void Player::Render()
	{
		mMesh->BindBuffer();
		mShader->Binds();
		GetDevice()->DrawIndexed(mMesh->GetIndexCount(), 0, 0);
	}
	void Player::SetVertices()
	{
		mVertices.resize(4);
		mVertices[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		mVertices[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		mVertices[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		mVertices[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		mVertices[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		mVertices[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		mVertices[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		mVertices[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	void Player::LoadBuffer()
	{
		mMesh = new Mesh();
		mMesh->CreateVertexBuffer(mVertices.data(), mVertices.size());

		std::vector<UINT> indices = {};
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);
		mMesh->CreateIndexBuffer(indices.data(), indices.size());

		mConstantBuffer = new ConstantBuffer(eCBType::Transform);
		mConstantBuffer->Create(sizeof(Vector4));

		Vector4 pos(0.0f, 0.0f, 0.0f, 1.0f);
		mConstantBuffer->SetData(&pos);
		mConstantBuffer->Bind(eShaderStage::VS);
	}
	void Player::LoadShader()
	{
		mShader = new Shader();
		mShader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		mShader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
	}
	void Player::SetUpState()
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
	Vector2 Player::GetInput()
	{
		Vector2 input = Vector2::Zero;
		if (Input::GetKey(eKeyCode::LEFT))
		{
			input = Vector2::Left;
		}

		if (Input::GetKey(eKeyCode::RIGHT))
		{
			input = Vector2::Right;
		}

		if (Input::GetKey(eKeyCode::UP))
		{
			input = Vector2::Up;
		}

		if (Input::GetKey(eKeyCode::DOWN))
		{
			input = Vector2::Down;
		}
		return input;
	}
}
