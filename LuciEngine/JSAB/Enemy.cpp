#include "Enemy.h"
#include "LSceneManager.h"
#include "LCamera.h"
#include "CameraScript.h"
namespace lu::JSAB
{
	void Enemy::Initialize()
	{
		Script::Initialize();
		mCamera = SceneManager::MainCamera()->Owner()->GetComponentsInChildren<CameraEffectScript>();
		BulletSetUp();
		DeActivate();
	}
	void Enemy::Update()
	{
		double time = mMusic->GetTime();
		CheckState(time);
		switch (mState)
		{
		case eState::DeActivate:
			return;
		case eState::Warning:
			WhileWarning(time);
			break;
		case eState::Activate:
			WhileActivate(time);
			break;
		case eState::Outro:
			WhileOutro(time);
			break;
		}
	}
	void Enemy::SetTimeline(MusicController* music, double wt, double at, double ot)
	{
		mMusic = music;
		mWarningTime = wt / 1000;
		mActivateTime = at / 1000;
		mOutroTime = ot / 1000;
	}
	void Enemy::DeActivate()
	{
		mState = eState::DeActivate;
		OnDeActivate();
	}
	void Enemy::CheckState(double time)
	{
		if (mState == eState::DeActivate)
		{
			if (mWarningTime >= 0.010)
				ChangeToWarning(time);
			else
				ChangeToActive(time);
		}
		else if (mState == eState::Warning)
		{
			ChangeToActive(time);
		}
		else if (mState == eState::Activate)
			if (mOutroTime >= 0.010)
				ChangeToOutro(time);
	}
	void Enemy::ChangeToWarning(double time)
	{
		if (time < mActivateTime - mWarningTime) return;
		mState = eState::Warning;
		OnWarning();
	}
	void Enemy::ChangeToActive(double time)
	{
		if (time < mActivateTime) return;
		mState = eState::Activate;
		OnActivate();
	}
	void Enemy::ChangeToOutro(double time)
	{
		if (time < mActivateTime + mOutroTime) return;
		mState = eState::Outro;
		OnOutro();
	}
}