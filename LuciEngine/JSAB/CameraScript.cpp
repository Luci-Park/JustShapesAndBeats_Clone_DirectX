#include "CameraScript.h"
#include "GeneralEffects.h"
#include "LObject.h"
#include "LAnimator.h"
#include "LMeshRenderer.h"
#include "LApplication.h"
#include "LTime.h"

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
	}

	void CameraScript::Update()
	{
		Flash();
		Beat();
	}

	void CameraScript::OnFlash()
	{
		mbIsFlashing = true;
	}
	void CameraScript::OnBeat(Vector3 dir)
	{
		mDefaultPos = mTransform->GetPosition();
		mbIsBeating = true;
		mBeatDir = dir;
	}

	void CameraScript::Flash()
	{
		static double duration = 0.05;
		static double time = 0;
		if (!mbIsFlashing) return;
		time += Time::DeltaTime();
		if (time < duration)
			mFlash->SetActive(true);
		else
		{
			mFlash->SetActive(false);
			time = 0;
			mbIsFlashing = false;
		}
	}
	void CameraScript::Beat()
	{
		static double duration = 0.05;
		static double time = 0;
		static float dist = 50;
		if (!mbIsBeating) return;
		time += Time::DeltaTime();
		if (time < duration)
		{
			Vector3 pos = Vector3::Lerp(mDefaultPos, mDefaultPos + mBeatDir * dist, time / duration);
			mTransform->SetPosition(pos);
		}
		else
		{
			mTransform->SetPosition(mDefaultPos);
			time = 0;
			mbIsBeating = false;
		}
	}
}