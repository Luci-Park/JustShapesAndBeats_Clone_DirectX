#include "CameraScript.h"
#include "GeneralEffects.h"
#include "LObject.h"
#include "LMeshRenderer.h"
#include "LApplication.h"
#include "LTime.h"

extern lu::Application application;
namespace lu::JSAB
{
	void CameraScript::Initialize()
	{
		Script::Initialize();
		mFlash = object::Instantiate<GameObject>(mTransform, eLayerType::UI)->AddComponent<MeshRenderer>();
		mFlash->SetMesh(Resources::Find<Mesh>(L"RectMesh"))
			->SetMaterial(GetGeneralMaterial(L"ThickBar"))->SetColor({1.f, 1.f, 1.f, 0.5})->UseColor(true);
		mFlash->Owner()->mTransform->SetScale(application.GetWidth(), application.GetHeight(), 1);
		mFlash->SetActive(false);
	}

	void CameraScript::Update()
	{
		Flash();
		Beat();
	}

	void CameraScript::OnWhiteFlash()
	{
		mbIsFlashing = true;
		mFlash->SetColor(Color::white);
	}
	void CameraScript::OnBlackFadeOut()
	{
	}
	void CameraScript::OnBeat(Vector3 dir)
	{
		mDefaultPos = mTransform->GetPosition();
		mbIsBeating = true;
		mBeatDir = dir;
	}
	void CameraScript::TurnEffectOff()
	{
		mFlash->SetActive(false);
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
	void CameraScript::FadeIn()
	{
		static double duration = 0.05;
		static double time = 0;
		if (!mbIsFadingIn) return;
		time += Time::DeltaTime();
		float t = 1 - time / duration;
		if (t <= 1.0f)
		{
			Color c = mFlash->GetColor();
			mFlash->SetColor(c.R(), c.G(), c.B(), t);
		}
		else
		{
			time = 0;
			mbIsFadingIn = false;
		}
	}
	void CameraScript::FadeOut()
	{
		static double duration = 0.05;
		static double time = 0;
		if (!mbIsFadingOut) return;
		time += Time::DeltaTime();
		float t = time / duration;
		if (t <= 1.0f)
		{
			Color c = mFlash->GetColor();
			mFlash->SetColor(c.R(), c.G(), c.B(), t);
		}
		else
		{
			time = 0;
			mbIsFadingOut = false;
		}
	}
}