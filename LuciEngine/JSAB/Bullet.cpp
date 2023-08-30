#include "Bullet.h"
#include "LGameObject.h"
#include "LTransform.h"
namespace lu::JSAB
{
	void Bullet::Initialize()
	{
		DeActivate();
	}
	void Bullet::Update()
	{
		if (BulletState::Active == mState)
			WhileActive();
		else if (BulletState::InActive == mState)
			WhileDeActive();
		else
			WhileShowing();
	}
	void Bullet::Show(double activateTime)
	{
		mActivateTime = activateTime;
		mState = BulletState::Show;
		OnShow();
	}
	void Bullet::Activate()
	{
		mState = BulletState::Active;
		OnActivate();
	}
	void Bullet::DeActivate()
	{
		mState = BulletState::InActive;
		OnDeActivate();
	}
}