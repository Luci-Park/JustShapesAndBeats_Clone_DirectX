#include "TutorialEightBulletScript.h"
#include "MusicController.h"
#include "LGameObject.h"
#include "LTime.h"
#include "LAnimator.h"
namespace lu::JSAB
{
#pragma region Interpolation 
	void InterpolationMove::Initialize()
	{
		mTr = Owner()->mTransform;
	}
	void InterpolationMove::Update()
	{
		mTime += Time::DeltaTime();
		float t = mTime / mDuration;
		if (t <= 1.0f)
		{
			Vector3 pos = Vector3::Lerp(mStartPos, mEndPos, t);
			mTr->SetLocalPosition(pos);
		}
		else
			Owner()->SetActive(false);
	}
#pragma endregion

#pragma region BurstParticle
	void BurstParticleScript::Initialize()
	{
		mTr = Owner()->mTransform;
		mMove = false;
		mSpeed = 330;
	}

	void BurstParticleScript::Update()
	{
		mTr->SetLocalPosition(mTr->GetLocalPosition() + mSpeed * Time::DeltaTime() * mDirection);
	}
	void BurstParticleScript::Reset()
	{
		mTr->SetLocalPosition(Vector3::Zero);
	}
#pragma endregion

#pragma region Burst
	void BurstScript::Initialize()
	{
		mTr = Owner()->mTransform;
		mAnim = Owner()->AddComponent<Animator>();
	}
	void BurstScript::Update()
	{/*
		mTime += Time::DeltaTime();
		double t = mTime / mDuration;
		if (t <= 1)
		{
			DisableBurst();
			mQuadCircle->SetActive(true);
			Vector3 scale = Vector3::Lerp(Vector3::Zero, Vector3::One, t);
			Vector3 pos = Vector3::Lerp(mStartPos, mTargetPos, t);
			mTr->SetScale(scale);
			mTr->SetPosition(pos);
		}
		else 
		{
			EnableBurst();
		}*/
	}
	void BurstScript::OnEnable()
	{
		DisableBurst();
	}
	void BurstScript::Reset()
	{
		mTime = 0;
		DisableBurst();
		mTr->SetScale(Vector3::Zero);
	}
	void BurstScript::EnableBurst()
	{
		mQuadCircle->SetActive(false);
		for (int i = 0; i < 8; i++)
		{
			mBursts[i]->Owner()->SetActive(true);
		}
	}
	void BurstScript::DisableBurst()
	{
		mQuadCircle->SetActive(true);
		for (int i = 0; i < 8; i++)
		{
			mBursts[i]->Reset();
			mBursts[i]->Owner()->SetActive(false);
		}
	}

	void BurstScript::CreateStraightDownAnimation(Vector3 startPos, Vector3 endPos, double duration)
	{
		Animation* ani = mAnim->CreateAnimation(L"straightDown");
		CreateStraightAnimation(ani, startPos, endPos, duration);
	}

	void BurstScript::CreateStraightUpAnimation(Vector3 startPos, Vector3 endPos, double duration)
	{
		Animation* ani = mAnim->CreateAnimation(L"straightUp");
		CreateStraightAnimation(ani, startPos, endPos, duration);
	}
	void BurstScript::CreateStraightFastAnimation(Vector3 startPos, Vector3 endPos, double duration)
	{
		Animation* ani = mAnim->CreateAnimation(L"straightFast");
		CreateStraightAnimation(ani, startPos, endPos, duration);
	}
	void BurstScript::CreateStraightAnimation(Animation* ani, Vector3 startPos, Vector3 endPos, double duration)
	{
		ani->AddPositionKey(0, startPos);
		Vector3 mid = Vector3::Lerp(startPos, endPos, 0.9);
		ani->AddPositionKey(duration * 0.7, mid);
		ani->AddPositionKey(duration, endPos);

		ani->AddScaleKey(0, Vector3::Zero);
		ani->AddScaleKey(duration, Vector3::One);

		ani->AddFunctionKey(0, std::bind(&BurstScript::DisableBurst, this));
		ani->AddFunctionKey(duration, std::bind(&BurstScript::EnableBurst, this));
	}
	void BurstScript::PlayStraightUp() { mAnim->PlayAnimation(L"straightUp", false); }
	void BurstScript::PlayStraightDown() { mAnim->PlayAnimation(L"straightDown", false); }


#pragma endregion
}
