#include "TutorialBeatBar.h"
#include "GeneralEffects.h"
#include "CameraScript.h"
#include "MusicController.h"
#include "TutorialManager.h"
#include "LResources.h"
#include "LApplication.h"
#include "LGameObject.h"
#include "LMeshRenderer.h"
#include "LCollider2D.h"
#include "LAnimator.h"
#include "LTime.h"
#include "LRenderer.h"

extern lu::Application application;
namespace lu::JSAB
{
	void TutorialBeatBar::Initialize()
	{
		Script::Initialize();

		Vector3 baseScale = { 20, (float)application.GetWidth() * 2, 1 };
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
	void TutorialBeatBar::OnShow()
	{
		mMr->SetActive(true);
		mAnim->SetActive(true);
		mAnim->PlayAnimation(L"Show", false);
	}
	void TutorialBeatBar::OnActivate()
	{
		mMr->SetActive(true);
		mAnim->SetActive(true);
		mAnim->PlayAnimation(L"Appear", false);
	}
	void TutorialBeatBar::OnDeActivate()
	{
		mCol->SetActive(false);
		mMr->SetActive(false);
		mAnim->SetActive(false);
	}
	void TutorialBeatBar::WhileShowing()
	{
		if (MusicController::_MusicController->GetTime() >= mActivateTime)
			Activate();
	}
	void TutorialBeatBar::WhileActive()
	{
	}
	void TutorialBeatBar::WhileDeActive()
	{
	}
	void TutorialBeatBar::CreateOnBeatAnimation()
	{
		Vector3 baseScale = { 20, (float)application.GetWidth() * 2, 1 };

		Animation* ani = mAnim->CreateAnimation(L"Show");
		ani->AddScaleKey(0, { 0, (float)application.GetWidth() * 2, 1 });
		ani->AddTintKey(0, Color::clear);
		ani->AddScaleKey(appearDuration, baseScale);
		ani->AddTintKey(appearDuration, {1.f, 1.f, 1.f, 0.8f});

		ani = mAnim->CreateAnimation(L"Appear");
		ani->AddColliderActiveKey(0, true);
		ani->AddScaleKey(0, { 20, 0, 1 });
		ani->AddInterpolationKey(0, 1);
		ani->AddTintKey(0, Color::white);

		ani->AddScaleKey(flashDuration, baseScale);
		ani->AddTintKey(flashDuration, Color::white);
		ani->AddInterpolationKey(flashDuration, 1);
		ani->AddInterpolationKey(flashDuration, 0);

		ani->AddFunctionKey(flashDuration, std::bind(&TutorialBeatBar::Beat, this));

		ani->AddScaleKey(flashDuration +stayDuration, baseScale);
		ani->AddScaleKey(flashDuration + stayDuration + disappearDuration, { 0, (float)application.GetWidth() * 2, 1 });
		ani->AddFunctionKey(flashDuration + stayDuration + disappearDuration, std::bind(&Bullet::DeActivate, this));

	}
	void TutorialBeatBar::Beat()
	{
		Quaternion rot = mTransform->GetRotation();
		if(rot == Quaternion::Identity)
			//position = {0, -application.GetHight() * 0.5f, 0);
			SceneManager::MainCamera()->Owner()->GetComponent<CameraScript>()->OnBeat(Vector3::Down);
		else if (rot == Quaternion::CreateFromAxisAngle(Vector3::Forward, PI*0.5))
			//position = { -application.GetWidth() * 0.5f,0, 0);
			SceneManager::MainCamera()->Owner()->GetComponent<CameraScript>()->OnBeat(Vector3::Left);
			//position = { application.GetWidth() * 0.5f,0, 0);
		else if (rot == Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI * 0.5))
			SceneManager::MainCamera()->Owner()->GetComponent<CameraScript>()->OnBeat(Vector3::Right);
		
	}
}