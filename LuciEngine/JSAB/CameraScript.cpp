#include "CameraScript.h"
#include "GeneralEffects.h"
#include "LObject.h"
#include "LAnimator.h"
#include "LMeshRenderer.h"
#include "LApplication.h"

extern lu::Application application;
namespace lu::JSAB
{
	void CameraScript::Initialize()
	{
		Script::Initialize();
		mFlash = object::Instantiate<GameObject>(mTransform, eLayerType::UI);
		mFlash->AddComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"))
			->SetMaterial(GetGeneralMaterial(L"ThickBar"))->SetColor({1.f, 1.f, 1.f, 0.5})->UseColor(true);
		mFlash->mTransform->SetScale(application.GetWidth(), application.GetHeight(), 1);
		mFlash->SetActive(false);

		mAnim = Owner()->AddComponent<Animator>();
		CreateAnimation();
	}
	void CameraScript::Flash()
	{
		mAnim->PlayAnimation(L"Flash", false);
	}
	void CameraScript::BeatUp()
	{
		mAnim->PlayAnimation(L"BeatUp", false);
	}
	void CameraScript::BeatDown()
	{
		mAnim->PlayAnimation(L"BeatDown", false);
	}
	void CameraScript::BeatLeft()
	{
		mAnim->PlayAnimation(L"BeatLeft", false);
	}
	void CameraScript::BeatRight()
	{
		mAnim->PlayAnimation(L"BeatRight", false);
	}
	void CameraScript::CreateAnimation()
	{
		double duration = 0.05;
		Animation* anim = mAnim->CreateAnimation(L"Flash");
		anim->AddFunctionKey(0, std::bind(&CameraScript::SetFlash, this, true));
		anim->AddFunctionKey(duration, std::bind(&CameraScript::SetFlash, this, false));

		int dist = 50;
		anim = mAnim->CreateAnimation(L"BeatUp");
		anim->AddPositionKey(0, Vector3::Zero);
		anim->AddPositionKey(duration * 0.5, Vector3::Up * 10);
		anim->AddPositionKey(duration, Vector3::Zero);

		anim = mAnim->CreateAnimation(L"BeatDown");
		anim->AddPositionKey(0, Vector3::Zero);
		anim->AddPositionKey(duration * 0.5, Vector3::Down * 10);
		anim->AddPositionKey(duration, Vector3::Zero);

		anim = mAnim->CreateAnimation(L"BeatLeft");
		anim->AddPositionKey(0, Vector3::Zero);
		anim->AddPositionKey(duration * 0.5, Vector3::Left * 10);
		anim->AddPositionKey(duration, Vector3::Zero);

		anim = mAnim->CreateAnimation(L"BeatRight");
		anim->AddPositionKey(0, Vector3::Zero);
		anim->AddPositionKey(duration * 0.5, Vector3::Right * 0);
		anim->AddPositionKey(duration, Vector3::Zero);
	}
}