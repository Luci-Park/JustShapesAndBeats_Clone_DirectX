#include "TutorialBeatCircle.h"
#include "GeneralEffects.h"
#include "MusicController.h"
#include "LGameObject.h"
#include "LResources.h"
#include "LMeshRenderer.h"
#include "LCollider2D.h"
#include "LAnimator.h"
#include "LCollider2D.h"

namespace lu::JSAB
{
	void TutorialBeatCircle::Initialize()
	{
		Script::Initialize();
		Owner()->SetName(L"BeatCircle");
		mTransform->SetScale({ 230, 230, 1 });
		mCol = Owner()->AddComponent<Collider2D>()->SetType(eColliderType::Circle);

		mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"circle_bullet_prep"));
		mMr->SetColor(Color::white)->UseColor(false);

		mReadySprite = Resources::Find<Texture>(L"circle_bullet_prep");
		mActivateSprite = Resources::Find<Texture>(L"circle_bullet");

		mAnim = Owner()->AddComponent<Animator>();
		CreateOnBeatAnimation();

		Bullet::Initialize();
	}
	void TutorialBeatCircle::OnShow()
	{
		mMr->SetActive(true);
		mAnim->SetActive(true);
		mAnim->PlayAnimation(L"Preparation", true);
	}
	void TutorialBeatCircle::OnActivate()
	{
		mMr->SetActive(true);
		mAnim->SetActive(true);
		mAnim->PlayAnimation(L"Activate", false);
	}
	void TutorialBeatCircle::OnDeActivate()
	{
		mCol->SetActive(false);
		mMr->SetActive(false);
		mAnim->SetActive(false);
		mTransform->SetScale({ 230, 230, 1 });
	}
	void TutorialBeatCircle::WhileShowing()
	{
		if (MusicController::_MusicController == nullptr) return;
		if (MusicController::_MusicController->GetTime() >= mActivateTime)
			Activate();
	}
	void TutorialBeatCircle::WhileActive()
	{
	}
	void TutorialBeatCircle::WhileDeActive()
	{
	}
	void TutorialBeatCircle::CreateOnBeatAnimation()
	{
		Animation* anim = mAnim->CreateAnimation(L"Preparation");
		anim->AddTextureKey(0, mReadySprite);
		CreateCounterClockwiseAnimation(0.5, anim);

		double duration = 0.3;
		anim = mAnim->CreateAnimation(L"Activate");
		anim->AddTextureKey(0, mActivateSprite);
		anim->AddColliderActiveKey(0, true);

		anim->AddInterpolationKey(0, 0);
		anim->AddInterpolationKey(duration * 0.7, 0.5);
		anim->AddInterpolationKey(duration * 0.9, 0.8);
		anim->AddInterpolationKey(duration, 0);

		anim->AddScaleKey(0, { 230, 230, 1 });
		anim->AddScaleKey(duration * 0.7, { 280, 280, 1 });
		anim->AddScaleKey(duration * 0.9, { 300, 300, 1 });
		anim->AddScaleKey(duration, { 0, 0 , 1 });

		anim->AddFunctionKey(duration, std::bind(&Bullet::DeActivate, this));
	}
}