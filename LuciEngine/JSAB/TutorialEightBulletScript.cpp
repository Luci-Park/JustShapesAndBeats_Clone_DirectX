#include "TutorialEightBulletScript.h"
#include "MusicController.h"
#include "LGameObject.h"
#include "LTime.h"
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
	}
	void BurstScript::Update()
	{
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
			mQuadCircle->SetActive(false);
			EnableBurst();
		}
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
		for (int i = 0; i < 8; i++)
		{
			mBursts[i]->Owner()->SetActive(true);
		}
	}
	void BurstScript::DisableBurst()
	{
		for (int i = 0; i < 8; i++)
		{
			mBursts[i]->Reset();
			mBursts[i]->Owner()->SetActive(false);
		}
	}

#pragma endregion
}
