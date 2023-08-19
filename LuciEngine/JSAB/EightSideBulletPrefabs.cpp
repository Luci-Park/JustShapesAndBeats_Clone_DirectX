#include "EightSideBulletPrefabs.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "GeneralEffects.h"
#include "LAnimator.h"
#include "LObject.h"
namespace lu::JSAB
{	
	void TutorialEightBullets::Initialize()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		SetMeshRenderer(mr);
		Animator* anim = AddComponent<Animator>();
		Animation* ani = anim->CreateAnimation(L"Rotate");

		float duration = 1.f;
		ani->AddRotationKey(0, Quaternion::Identity);
		ani->AddRotationKey(duration * .25, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI * 0.5));
		ani->AddRotationKey(duration * .5, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI));
		ani->AddRotationKey(duration * .75, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI * 1.5));
		ani->AddRotationKey(duration, Quaternion::CreateFromAxisAngle(Vector3::Forward, PI * -2));
		anim->PlayAnimation(L"Rotate", true);
		
		CreateEnterEffect(); 
		mTransform->SetPosition(Vector3(500, -51, 0));
		mTransform->SetScale(Vector3(42, 42, 1));
	}
	void TutorialEightBullets::SetMeshRenderer(MeshRenderer* mr)
	{
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"octa_circle_bullet"));
	}
	void TutorialEightBullets::SetEnterEffect(MeshRenderer* mr)
	{
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"circle_bullet_blink_white"));
	}
	void TutorialEightBullets::CreateEnterEffect()
	{
		GameObject* enterEffect = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
		MeshRenderer* mr = enterEffect->AddComponent<MeshRenderer>();
		SetEnterEffect(mr);
		enterEffect->mTransform->SetLocalPosition({ 0, 0, -1 });

		Animator* anim = enterEffect->AddComponent<Animator>();
		Animation* ani = anim->CreateAnimation(L"Appear");
		float duration = 0.5;
		ani->AddTintKey(0, Color::white);
		ani->AddTintKey(duration, {1, 1, 1, 0});
		ani->AddLocalScaleKey(0, { 0, 0, 1 });
		ani->AddLocalScaleKey(0.1, { 1, 1, 1 });
		ani->AddLocalScaleKey(duration, { 0, 0, 1 });
		anim->PlayAnimation(L"Appear", true);
	}
}