#include "CameraScript.h"
#include "GeneralEffects.h"
#include "LObject.h"
#include "LMeshRenderer.h"
#include "LApplication.h"
#include "LAnimator.h"
#include "LTime.h"

extern lu::Application application;
namespace lu::JSAB
{
	void CameraScript::Initialize()
	{
		Script::Initialize();
		mAnim = Owner()->AddComponent<Animator>();
		{
			auto a = mAnim->CreateAnimation(L"BumpUp");
			a->AddPositionYKey(0, 0);
			a->AddPositionYKey(0.025, 50);
			a->AddPositionYKey(0.05, 0);
			
			a = mAnim->CreateAnimation(L"BumpDown");
			a->AddPositionYKey(0, 0);
			a->AddPositionYKey(0.025, -50);
			a->AddPositionYKey(0.05, 0);

			a = mAnim->CreateAnimation(L"BumpRight");
			a->AddPositionXKey(0, 0);
			a->AddPositionXKey(0.025, 50);
			a->AddPositionXKey(0.05, 0);

			a = mAnim->CreateAnimation(L"BumpLeft");
			a->AddPositionXKey(0, 0);
			a->AddPositionXKey(0.025, -50);
			a->AddPositionXKey(0.05, 0);
		}


		GameObject* flash = object::Instantiate<GameObject>(mTransform, eLayerType::UI);
		flash->AddComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"ThickBar"))->SetColor({1.f, 1.f, 1.f, 0.5})->UseColor(true);
		flash->mTransform->SetScale(application.GetWidth(), application.GetHeight(), 1);
		flash->mTransform->SetPosition({ 0, 0, -5 });
		mFlash = flash->AddComponent<Animator>();
		{
			auto a = mFlash->CreateAnimation(L"WhiteFlash");
			a->AddColorKey(0, {1, 1, 1, 0});
			a->AddColorKey(0.025, {1, 1, 1, 1});
			a->AddColorKey(0.05, {1, 1, 1, 0});

			a = mFlash->CreateAnimation(L"BlackFlash");
			a->AddColorKey(0, { 0, 0, 0, 0 });
			a->AddColorKey(0.025, { 0, 0, 0, 1 });
			a->AddColorKey(0.05, { 0, 0, 0, 0 });

			a = mFlash->CreateAnimation(L"BlackFade");
			a->AddColorKey(0, { 0, 0, 0, 0.5 });
			a->AddColorKey(0.5, { 0, 0, 0, 1 });
		}
		Reset();
	}
	void CameraScript::Bump(Vector3 dir)
	{
		if (dir == Vector3::Up)
			mAnim->PlayAnimation(L"BumpUp", false);
		if (dir == Vector3::Down)
			mAnim->PlayAnimation(L"BumpDown", false);
		if (dir == Vector3::Left)
			mAnim->PlayAnimation(L"BumpRight", false);
		if (dir == Vector3::Right)
			mAnim->PlayAnimation(L"BumpLeft", false);
	}
	void CameraScript::WhiteFlash()
	{
		mFlash->PlayAnimation(L"WhiteFlash", false);
	}
	void CameraScript::BlackFlash()
	{
		mFlash->PlayAnimation(L"BlackFlash", false);
	}
	void CameraScript::BlackFadeOut()
	{
		mFlash->PlayAnimation(L"BlackFade", false);
	}
	void CameraScript::Reset()
	{
		mTransform->SetPosition({ 0, 0, -10 });
		mFlash->Owner()->GetComponent<MeshRenderer>()->SetColor(Color::clear);
	}
}