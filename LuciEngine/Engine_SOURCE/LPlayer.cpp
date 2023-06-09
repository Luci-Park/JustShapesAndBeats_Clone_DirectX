#include "LPlayer.h"
#include "LInput.h"
#include "LTime.h"
namespace lu
{
	Player::Player()
		: mPos(Vector2::Zero)
		, mRadius(0.05f)
		, mMass(0)
	{
	}
	Player::~Player()
	{
	}
	void Player::Initialize()
	{
	}
	void Player::Update()
	{
		Move();
		CheckMass();
	}
	void Player::LateUpdate()
	{
	}
	void Player::Render()
	{
		UpdateConst();
		GameObject::Render();
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
		renderer::constantBuffer->SetData(&pos);
		renderer::constantBuffer->Bind(eShaderStage::VS);
	}
}
