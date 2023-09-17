#include "CameraScript.h"
#include "GeneralEffects.h"
#include "LObject.h"
#include "LMeshRenderer.h"
#include "LApplication.h"
#include "LAnimator.h"
#include "LTime.h"
#include "LCamera.h"

extern lu::Application application;
namespace lu::JSAB
{
#pragma region Camera Effect
	void CameraEffectScript::Initialize()
	{
		Script::Initialize();
		mAnim = Owner()->AddComponent<Animator>();
		{
			auto a = mAnim->CreateAnimation(L"BumpUp");
			a->AddLocalPositionKey(0, { 0, 0, 0 });
			a->AddLocalPositionKey(0.025, { 0, 50, 0 });
			a->AddLocalPositionKey(0.05, { 0, 0, 0 });
			
			a = mAnim->CreateAnimation(L"BumpDown");
			a->AddLocalPositionKey(0, { 0, 0, 0 });
			a->AddLocalPositionKey(0.025, { 0, -50, 0 });
			a->AddLocalPositionKey(0.05, { 0, 0, 0 });

			a = mAnim->CreateAnimation(L"BumpRight");
			a->AddLocalPositionKey(0, { 0, 0, 0 });
			a->AddLocalPositionKey(0.025, { 50, 0, 0 });
			a->AddLocalPositionKey(0.05, { 0, 0, 0 });

			a = mAnim->CreateAnimation(L"BumpLeft");
			a->AddLocalPositionKey(0, { 0, 0, 0 });
			a->AddLocalPositionKey(0.025, { -50, 0, 0 });
			a->AddLocalPositionKey(0.05, { 0, 0, 0 });
		}


		GameObject* flash = object::Instantiate<GameObject>(mTransform, eLayerType::UI);
		auto m = flash->AddComponent<MeshRenderer>()->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		m->SetColor({ 1.f, 1.f, 1.f, 0.5 })->UseColor(true);

		std::shared_ptr<Material> mat = Resources::Load<Material>(L"CameraFlashMat", L"ThickBar");
		mat->SetRenderingMode(eRenderingMode::Transparent);
		m->SetMaterial(mat);

		flash->mTransform->SetScale(application.GetWidth(), application.GetHeight(), 1);
		flash->mTransform->SetLocalPosition({ 0, 0, 1 });
		flash->SetName(L"Camera Flash");
		mFlash = flash->AddComponent<Animator>();
		{
			auto a = mFlash->CreateAnimation(L"WhiteFlash");
			a->AddColorKey(0, {1, 1, 1, 0});
			a->AddColorKey(0.025, {1, 1, 1, 0.3});
			a->AddColorKey(0.05, {1, 1, 1, 0});

			a = mFlash->CreateAnimation(L"BlackFlash");
			a->AddColorKey(0, { 0, 0, 0, 0 });
			a->AddColorKey(0.025, { 0, 0, 0, 1 });
			a->AddColorKey(0.05, { 0, 0, 0, 0 });

			a = mFlash->CreateAnimation(L"BlackFadeOut");
			a->AddColorKey(0, { 0, 0, 0, 0.5 });
			a->AddColorKey(0.5, { 0, 0, 0, 1 });

			a = mFlash->CreateAnimation(L"BlackFadeIn");
			a->AddColorKey(0, { 0, 0, 0, 1 });
			a->AddColorKey(0.5, { 0, 0, 0, 0 });
		}
		Reset();
	}
	void CameraEffectScript::Bump(Vector3 dir)
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
	void CameraEffectScript::WhiteFlash()
	{
		mFlash->PlayAnimation(L"WhiteFlash", false);
	}
	void CameraEffectScript::BlackFlash()
	{
		mFlash->PlayAnimation(L"BlackFlash", false);
	}
	void CameraEffectScript::BlackFadeOut()
	{
		mFlash->PlayAnimation(L"BlackFadeOut", false);
	}
	void CameraEffectScript::BlackFadeIn()
	{
		mFlash->PlayAnimation(L"BlackFadeIn", false);
	}
	void CameraEffectScript::Reset()
	{
		mTransform->SetLocalPosition(Vector3::Zero);
		mFlash->Owner()->GetComponent<MeshRenderer>()->SetColor(Color::clear);
	}
#pragma endregion

#pragma region GameCamera
	void GameCamera::Initialize()
	{
		Script::Initialize();
		{
			Owner()->SetName(L"CameraParent");
			mTransform->SetPosition({ 0, 0, -10 });
			auto c = Owner()->AddComponent<Camera>();
			for (int i = 0; i < (UINT)eLayerType::End; i++)
			{
				c->TurnLayerMask((eLayerType)i, false);
			}
		}
		{
			auto g = object::Instantiate<GameObject>(mTransform, eLayerType::Camera);
			g->SetName(L"Main Camera");
			auto c = g->AddComponent<Camera>();
			bool active[] = { true, true, true, true, false, false };
			for (int i = 0; i < (UINT)eLayerType::End; i++)
				c->TurnLayerMask((eLayerType)i, active[i]);
			mEffect = g->AddComponent<CameraEffectScript>();
		}
	}
#pragma endregion

}