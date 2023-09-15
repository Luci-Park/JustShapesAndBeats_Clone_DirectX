#include "Bullet.h"
#include "LSceneManager.h"
#include "LCamera.h"
namespace lu::JSAB
{
	void Bullet::Initialize()
	{
		Script::Initialize();
		mCamera = SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect();
		BulletSetUp();
		DeActivate();
	}
	void Bullet::Update()
	{
		double time = mMusic->GetTime();
		TimeCheck(time);
	}
	void Bullet::SetTimeline(MusicController* music, double wt, double at, double ot)
	{
		mMusic = music;
		mWarningTime = wt / 1000;
		mActivateTime = at / 1000;
		mOutroTime = ot / 1000;
	}
	void Bullet::DeActivate()
	{
		mState = eState::DeActivate;
		OnDeActivate();
	}
	void Bullet::TestTime(double time)
	{
		TimeCheck(time);
	}
	void Bullet::TimeCheck(double time)
	{
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
	Vector2 Bullet::PathInCircle(double durationforacircle, double time, float radius)
	{
		durationforacircle = 1 / durationforacircle;
		double angle = 2.0 * PI * durationforacircle * time;

		float x = radius * static_cast<float>(cos(angle));
		float y = radius * static_cast<float>(sin(angle));

		return Vector2(x, y);
	}
	void Bullet::CheckState(double time)
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
		if (mState == eState::Activate)
			if (mOutroTime >= 0.010)
				ChangeToOutro(time);
		if (mState == eState::Outro && time >= mActivateTime + mOutroTime)
		{
			DeActivate();
		}
	}
	void Bullet::ChangeToWarning(double time)
	{
		if (time < mActivateTime - mWarningTime) return;
		mState = eState::Warning;
		OnWarning();
	}
	void Bullet::ChangeToActive(double time)
	{
		if (time < mActivateTime) return;
		mState = eState::Activate;
		OnActivate();
	}
	void Bullet::ChangeToOutro(double time)
	{
		if (time < mActivateTime + mOutroTime) return;
		mState = eState::Outro;
		OnOutro();
	}
}