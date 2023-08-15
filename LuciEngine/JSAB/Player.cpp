#include "Player.h"
#include "LInput.h"
#include "LGameObject.h"
#include "LTransform.h"
#include "LTime.h"
#include "LCollider2D.h"
namespace lu::JSAB
{
	Player::Player()
		: mMoveSpeed(280.0f)
		, mDashSpeed(1120.0f)
		, mDashTimer(0.0f)
		, mDashDuration(0.1f)
		, mMoveDir(Vector3::Zero)
		, mIsDashing(false)
	{
	}
	void Player::Initialize()
	{
		mTr = GetOwner()->mTransform;
		mCr = GetOwner()->GetComponent<Collider2D>();
		mOrgScale = mTr->GetScale();
		mMoveScale = { mOrgScale.x * 0.7f, mOrgScale.y * 1.3f, 1.f };
		mDashScale = { mOrgScale.x * 0.5f, mOrgScale.y * 2.f, 1.f };
	}
	void Player::Update()
	{
		Vector3 moveDir = GetInputDir();
		if (Input::GetKeyDown(eKeyCode::SPACE) && !mIsDashing)
		{
			mIsDashing = true;
			mDashTimer = 0.f;
			mDashDir = moveDir == Vector3::Zero ? Vector3::Right : moveDir;
		}

		if (!mIsDashing)
		{
			mCr->SetState(eState::Active);
			mDashOutline->SetState(eState::InActive);
			mTr->SetPosition(mTr->GetPosition() + moveDir * mMoveSpeed * Time::DeltaTime());
			MoveRotate(GetRotation(moveDir));
			MoveScale(GetMoveScale(moveDir));
		}
		else
		{
			mDashTimer += Time::DeltaTime();
			if (mDashTimer > mDashDuration) mIsDashing = false;

			mCr->SetState(eState::InActive);
			mDashOutline->SetState(eState::Active);

			mTr->SetPosition(mTr->GetPosition() + mDashDir * mDashSpeed * Time::DeltaTime());
			MoveRotate(GetRotation(mDashDir));
			mTr->SetScale(mDashScale);
		}

	}
	void Player::MoveRotate(Quaternion rotation)
	{
		static Quaternion originalRotation;
		static Quaternion targetRotation = Quaternion::Identity;
		static float timer = 0;
		static float rotateTime = 0.05f;
		if (rotation != targetRotation)
		{
			originalRotation = mTr->GetRotation();
			targetRotation = rotation;
			timer = 0;
			mTr->SetRotation(Quaternion::Identity);
			return;
		}
		if (timer <= rotateTime)
		{
			timer += Time::DeltaTime();
			mTr->SetRotation(Quaternion::Lerp(originalRotation, targetRotation, timer / rotateTime));
		}
		else
		{
			mTr->SetRotation(rotation);
		}
	}
	void Player::MoveScale(Vector3 scale)
	{
		static Vector3 originalScale;
		static Vector3 targetScale = Vector3::One;
		static float timer = 0;
		static float scaleTime = 0.15f;
		if (scale != targetScale)
		{
			originalScale = mTr->GetScale();
			targetScale = scale;
			timer = 0;
			mTr->SetScale(mOrgScale);
			return;
		}
		if (timer <= scaleTime)
		{
			timer += Time::DeltaTime();
			mTr->SetScale(Vector3::Lerp(originalScale, targetScale, timer / scaleTime));
		}
		else
		{
			mTr->SetScale(scale);
		}
	}
	Vector3 Player::GetMoveScale(Vector3 direction)
	{
		static Vector3 prevDir = Vector3::Zero;
		if (direction == Vector3::Zero || direction != prevDir)
		{
			prevDir = direction;
			return mOrgScale;
		}
		else
		{
			return mMoveScale;
		}
	}
	Vector3 Player::GetInputDir()
	{
		Vector3 moveDir = Vector3::Zero;
		if (Input::GetKey(eKeyCode::LEFT))
			moveDir = Vector3::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			moveDir = Vector3::Right;
		if (Input::GetKey(eKeyCode::UP))
			moveDir = Vector3::Up;
		if (Input::GetKey(eKeyCode::DOWN))
			moveDir = Vector3::Down;
		return moveDir;
	}
	Quaternion Player::GetRotation(Vector3 moveDir)
	{
		float radian = 0;
		if (moveDir == Vector3::Left)
			radian = PI * 0.5f;
		if (moveDir == Vector3::Right)
			radian = -PI * 0.5f;
		if (moveDir == Vector3::Down)
			radian = PI;

		return Quaternion::CreateFromAxisAngle(Vector3::Forward, radian);
	}
}
