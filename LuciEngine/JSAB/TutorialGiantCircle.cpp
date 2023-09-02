#include "TutorialGiantCircle.h"
#include "GeneralEffects.h"
#include "LMeshRenderer.h"
#include "LGameObject.h"
#include "LResources.h"
#include "LAnimator.h"
#include "MusicController.h"
namespace lu::JSAB
{
	TutorialGiantCircle::TutorialGiantCircle()
	{
	}
	TutorialGiantCircle::~TutorialGiantCircle()
	{
	}
	void TutorialGiantCircle::Initialize()
	{
		Script::Initialize();
		mTransform->SetScale(Vector3::Zero);
		Owner()->SetName(L"GiantCircle");
		mMr = Owner()->AddComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"circle_bullet"));
		mMr->SetColor(Color::white);
		mAnim = Owner()->AddComponent<Animator>();
		CreateAnimation();
		Bullet::Initialize();
	}
	void TutorialGiantCircle::ActivateWithTime(double time)
	{
		mAnim->PlayAnimation(L"Bump", true);
		mAnim->SetTime(time);
		Activate();
	}
	void TutorialGiantCircle::OnShow()
	{
		Owner()->SetActive(true);
		mTransform->SetScale(Vector3::Zero);
		mMr->UseColor(false);
	}
	void TutorialGiantCircle::OnDeActivate()
	{
		mAnim->PlayAnimation(L"Disappear", false);
		mTime = 111.611;
	}
	void TutorialGiantCircle::WhileShowing()
	{
 		if (MusicController::Instance == nullptr) return;
		double currTime = MusicController::Instance->GetTime();

		if (currTime >= mTime)
		{
			mTime += 0.108;
			Vector3 scale = mTransform->GetScale();
			scale.x += 7;
			scale.y += 7;
			mTransform->SetScale(scale);
		}
	}
	void TutorialGiantCircle::WhileActive()
	{

	}
	void TutorialGiantCircle::CreateAnimation()
	{
		auto a = mAnim->CreateAnimation(L"Disappear");
		double duration = 0.432;
		a->AddScaleKey(0, {740, 740, 1});
		a->AddScaleKey(duration * 0.7, { 760, 760, 1 });
		a->AddScaleKey(duration, Vector3::Zero);

		a->AddInterpolationKey(0, 1);
		a->AddInterpolationKey(duration * 0.3, 0);
		a->AddInterpolationKey(duration * 0.6, 1);
		a->AddInterpolationKey(duration * 0.9, 0);
		a->AddInterpolationKey(duration * 1, 1);

		a->AddFunctionKey(duration, std::bind(&GameObject::SetActive, Owner(), false));



		a = mAnim->CreateAnimation(L"Bump");
		a->AddScaleKey(duration * 0, {40.f, 40.f, 1.f});
		a->AddInterpolationKey(duration * 0, 0);
		a->AddScaleKey(duration * .25, { 760, 760, 1 });
		a->AddInterpolationKey(duration * .25, 1);
		a->AddScaleKey(duration * .5, { 40.f, 40.f, 1.f });
		a->AddInterpolationKey(duration * .5, 0);
		a->AddScaleKey(duration * .75, { 760, 760, 1 });
		a->AddInterpolationKey(duration * .75, 1);
		a->AddScaleKey(duration, { 40.f, 40.f, 1.f });
		a->AddInterpolationKey(duration, 0);


	}
}