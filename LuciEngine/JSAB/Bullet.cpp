#include "Bullet.h"
#include "LGameObject.h"
#include "LTransform.h"
namespace lu::JSAB
{
	void Bullet::Initialize()
	{
		DeActivate();
	}
	void Bullet::Show()
	{
		OnShow();
	}
	void Bullet::Activate()
	{
		isActive = true;
		OnActivate();
	}
	void Bullet::DeActivate()
	{
		isActive = false;
		OnDeActivate();
	}
}