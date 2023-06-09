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
		, mRadius(0.05f)
		, mMass(0)
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
		Move();
		CheckMass();
		UpdateConst();
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
		Vector4 color(GetRandomInt(0, 255) / 255.0f, GetRandomInt(0, 255) / 255.0f, GetRandomInt(0, 255) / 255.0f, 1.0f);
		int segments = 30;

		float angleIncrement = std::numbers::pi * 2 / segments;
		float angle = 0.0f;
		
		mVertices.resize(segments + 1);

		for (int i = 0; i <= segments; i++, angle += angleIncrement)
		{
			float x = cos(angle);
			float y = sin(angle);

			mVertices[i].pos = Vector3(x, y, 0.0f);
			mVertices[i].color = color;
		}
		mVertices[segments].pos = Vector3::Zero;
		mVertices[segments].color = color;
	}
	void Player::LoadBuffer()
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

		Vector4 pos(0.0f, 0.0f, 0.0f, mRadius);
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
	void Player::Move()
	{
		float moveSpeed = 0.6f;
		Vector2 dir = GetInput();
		mPos += dir * moveSpeed * Time::DeltaTime();
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
	void Player::CheckMass()
	{
		if (Input::GetKeyDown(eKeyCode::Q))
			mMass++;
	}
	void Player::UpdateConst()
	{
		Vector4 pos;
		pos.x = mPos.x;
		pos.y = mPos.y;
		pos.z = 0;
		pos.w = mRadius + mMass * 0.005;
		mConstantBuffer->SetData(&pos);
		mConstantBuffer->Bind(eShaderStage::VS);
	}
}
