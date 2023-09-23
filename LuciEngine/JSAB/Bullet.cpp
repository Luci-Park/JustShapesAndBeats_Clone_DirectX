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
		Owner()->SetTag(eTagType::Bullet);
		mBulletState = eBulletState::Waiting;
		BulletSetUp();
		DeActivate();
	}
	void Bullet::Update()
	{
		mBounds = SceneManager::MainCamera()->GetBoundary();
		if (mMusic == nullptr) 
			return;
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
	void Bullet::Warning()
	{
		mBulletState = eBulletState::Warning;
		OnWarning();
	}
	void Bullet::Activate()
	{
		mBulletState = eBulletState::Activate;
		OnActivate();
	}
	void Bullet::Outro()
	{
		mBulletState = eBulletState::Outro;
		OnOutro();
	}
	void Bullet::DeActivate()
	{
		mBulletState = eBulletState::DeActivate;
		OnDeActivate();
	}
	void Bullet::TestTime(double time)
	{
		TimeCheck(time);
	}
	void Bullet::TimeCheck(double time)
	{
		CheckState(time);
		switch (mBulletState)
		{
		case eBulletState::DeActivate:
			return;
		case eBulletState::Warning:
			mWarningProcess = 1 - (mActivateTime - time) / mWarningTime;
			WhileWarning(time);
			break;
		case eBulletState::Activate:
			mActivateProcess = 1 - (time - mActivateTime) / mOutroTime;
			WhileActivate(time);
			break;
		case eBulletState::Outro:
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
		if (mBulletState == eBulletState::DeActivate && time <= mActivateTime)
			mBulletState = eBulletState::Waiting;
		if (mBulletState == eBulletState::Waiting)
		{
			if (mWarningTime >= 0.001)
				ChangeToWarning(time);
			else
				ChangeToActive(time);
		}
		else if (mBulletState == eBulletState::Warning)
		{
			ChangeToActive(time);
		}
		else if (mBulletState == eBulletState::Activate)
		{
			if (time == mActivateTime)
				ChangeToActive(time);
			else if (mOutroTime >= 0.001)
				ChangeToOutro(time);
		}
	}
	void Bullet::ChangeToWarning(double time)
	{
		if (mActivateTime - mWarningTime <= time && time < mActivateTime)
		{
			Warning();
		}
	}
	void Bullet::ChangeToActive(double time)
	{
		if (mActivateTime<= time)
		{
			Activate();
		}
	}
	void Bullet::ChangeToOutro(double time)
	{
		if (mActivateTime + mOutroTime<= time)
		{
			Outro();
		}
	}
}