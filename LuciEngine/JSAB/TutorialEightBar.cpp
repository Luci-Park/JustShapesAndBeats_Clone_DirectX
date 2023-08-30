#include "TutorialEightBar.h"
#include "TutorialEightBullets.h"
#include "LObject.h"
#include "LGameObject.h"
namespace lu::JSAB
{
	void TutorialEightBar::Initialize()
	{
		Script::Initialize();
		for (int i = 0; i < 10; i++)
		{
			mBullets[i] = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TutorialEightBullets>();
			mBullets[i]->mTransform->SetLocalPosition({ 0, -200.f + 40.f * i, 0 });
		}
		Bullet::Initialize();
	}
	void TutorialEightBar::OnActivate()
	{
		for (int i = 0; i < 10; i++)
			mBullets[i]->Activate();
	}
	void TutorialEightBar::OnDeActivate()
	{
		for (int i = 0; i < 10; i++)
			mBullets[i]->DeActivate();
	}
	void TutorialEightBar::WhileActive()
	{
	}
}