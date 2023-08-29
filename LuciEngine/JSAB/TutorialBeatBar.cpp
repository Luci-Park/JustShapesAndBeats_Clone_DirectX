#include "TutorialBeatBar.h"
#include "GeneralEffects.h"
#include "resource.h"
#include "LApplication.h"
#include "LGameObject.h"
#include "LMeshRenderer.h"
#include "LCollider2D.h"
#include "LAnimator.h"
#include "LTime.h"

extern lu::Application application;
namespace lu::JSAB
{
	void TutorialBeatBar::Initialize()
	{
		Script::Initialize();

		Vector3 baseScale = { 20, (float)application.GetHeight() * 2, 1 };
		Owner()->SetName(L"BeatBar");
		mTransform->SetPosition(Vector3::Up * (float)application.GetHeight() * 0.5);
		mTransform->SetScale(baseScale);

		mCol = Owner()->AddComponent<Collider2D>();

		mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"verticlebar"));
		mMr->SetColor(Color::white)->UseColor(false);

		mAnim = Owner()->AddComponent<Animator>();
		CreateOnBeatAnimation();

		Bullet::Initialize();
	}
	void TutorialBeatBar::OnActivate()
	{
		mMr->SetActive(true);
		mAnim->SetActive(true);
		mAnim->PlayAnimation(L"OnBeat", false);
	}
	void TutorialBeatBar::OnDeActivate()
	{
		mCol->SetActive(false);
		mMr->SetActive(false);
		mAnim->SetActive(false);
	}
	void TutorialBeatBar::WhileActive()
	{
	}
	void TutorialBeatBar::WhileDeActive()
	{
	}
	void TutorialBeatBar::CreateOnBeatAnimation()
	{
		Vector3 baseScale = { 20, (float)application.GetHeight() * 2, 1 };

		Animation* ani = mAnim->CreateAnimation(L"OnBeat");
		ani->AddColliderActiveKey(0, false);
		ani->AddScaleKey(0, { 0, (float)application.GetHeight() * 2, 1 });
		ani->AddTintKey(0, Color::clear);
		ani->AddInterpolationKey(0, 0);

		ani->AddScaleKey(appearDuration, baseScale);
		ani->AddTintKey(appearDuration, Color::white);
		ani->AddInterpolationKey(appearDuration, 0);

		ani->AddColliderActiveKey(appearDuration, true);
		ani->AddScaleKey(appearDuration, { 20, 0, 1 });
		ani->AddInterpolationKey(appearDuration, 1);
		ani->AddScaleKey(appearDuration + flashDuration, baseScale);
		ani->AddInterpolationKey(appearDuration + flashDuration, 1);
		ani->AddInterpolationKey(appearDuration + flashDuration, 0);

		ani->AddScaleKey(appearDuration + flashDuration +stayDuration, baseScale);
		ani->AddScaleKey(appearDuration + flashDuration + stayDuration + disappearDuration, { 0, (float)application.GetHeight() * 2, 1 });
		ani->AddFunctionKey(appearDuration + flashDuration + stayDuration + disappearDuration, std::bind(&Bullet::DeActivate, this));

	}
}