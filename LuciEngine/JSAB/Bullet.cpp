#include "Bullet.h"
#include "LSceneManager.h"
#include "LCamera.h"
namespace lu::JSAB
{
	void Bullet::Initialize()
	{
		Script::Initialize();
		mCamera = SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect();
		mBounds = SceneManager::MainCamera()->GetBoundary();
		BulletSetUp();
		DeActivate();
		mState = eState::Waiting;
	}
	void Bullet::Update()
	{
		mBounds = SceneManager::MainCamera()->GetBoundary();
		if (mMusic == nullptr) return;
		double time = mMusic->GetTime();
		TimeCheck(time);
	}
	void Bullet::SetTimeline(MusicController* music, double wt, double at, double ot)
	{
		mMusic = music;
		mWarningTime = wt;
		mActivateTime = at;
		mOutroTime = ot;
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
			mWarningProcess = 1 - (mActivateTime - time) / mWarningTime;
			WhileWarning(time);
			break;
		case eState::Activate:
			mActivateProcess = 1 - (time - mActivateTime) / mOutroTime;
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
		if (mState == eState::DeActivate && time <= mActivateTime)
			mState = eState::Waiting;
		if (mState == eState::Waiting)
		{
			if (mWarningTime >= 0.001)
				ChangeToWarning(time);
			else
				ChangeToActive(time);
		}
		else if (mState == eState::Warning)
		{
			ChangeToActive(time);
		}
		if (mState == eState::Activate)
			if (mOutroTime >= 0.001)
				ChangeToOutro(time);
	}
	void Bullet::ChangeToWarning(double time)
	{
		if (mActivateTime - mWarningTime <= time && time < mActivateTime)
		{
			mState = eState::Warning;
			OnWarning();
		}
	}
	void Bullet::ChangeToActive(double time)
	{
		if (mActivateTime<= time)
		{
			mState = eState::Activate;
			OnActivate();
		}
	}
	void Bullet::ChangeToOutro(double time)
	{
		if (mActivateTime + mOutroTime<= time)
		{
			mState = eState::Outro;
			OnOutro();
		}
	}
}