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
		mMr->GetMaterial()->SetRenderingMode(eRenderingMode::Transparent);
		mAnim = Owner()->AddComponent<Animator>();
		CreateAnimation();
		Bullet::Initialize();
	}
	void TutorialGiantCircle::OnShow()
	{
		Owner()->SetActive(true);
	}
	void TutorialGiantCircle::OnDeActivate()
	{
		//mAnim->PlayAnimation(L"Disappear", false);
		mTime = 111.611;
	}
	void TutorialGiantCircle::WhileShowing()
	{
		if (MusicController::Instance == nullptr) return;
		if (MusicController::Instance->GetTime() >= mTime)
		{
			mTime += 0.432;
			Vector3 scale = mTransform->GetScale();
			scale.x += 0.04;
			scale.y += 0.04;
			mTransform->SetScale(scale);
			if (mTime > 123.2)
				DeActivate();
		}
	}
	void TutorialGiantCircle::WhileActive()
	{
	}
	void TutorialGiantCircle::CreateAnimation()
	{
		auto a = mAnim->CreateAnimation(L"Disappear");
		a->AddScaleKey(0, {760, 760, 1});
		a->AddScaleKey(0.1, Vector3::Zero);
		a->AddInterpolationKey(0, 0);
		a->AddFunctionKey(0.1, std::bind(&GameObject::SetActive, Owner(), false));
	}
}