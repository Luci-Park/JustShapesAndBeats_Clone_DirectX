#include "TutorialBulletPrefabs.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "LCollider2D.h"
#include "GeneralEffects.h"
#include "LAnimator.h"
#include "LObject.h"
#include "LApplication.h"

extern lu::Application application;
namespace lu::JSAB
{	
#pragma region Tutorial Eight Bullets

	void TutorialEightBulletsPrefab::Initialize()
	{
		SetName(L"EightSideBullet");
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
		AddComponent<Collider2D>()->SetType(eColliderType::Circle);
	}
	void TutorialEightBulletsPrefab::SetMeshRenderer(MeshRenderer* mr)
	{
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"octa_circle_bullet"));
	}
	void TutorialEightBulletsPrefab::SetEnterEffect(MeshRenderer* mr)
	{
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"circle_bullet_blink_white"));
	}
	void TutorialEightBulletsPrefab::CreateEnterEffect()
	{
		GameObject* enterEffect = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
		enterEffect->SetName(L"enterburst");
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

#pragma endregion

#pragma region
	void TutorialBurstBulletsPrefab::Initialize()
	{
		{
			GameObject* fourSide = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
			fourSide->mTransform->SetScale({ 30, 30, 1 });
			fourSide->SetName(L"burstBullet");
			MeshRenderer* mr = fourSide->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"quad_circle_bullet"));
			mr->SetColor(Color::white);
			Animator* anim = fourSide->AddComponent<Animator>();
			Animation* ani = anim->CreateAnimation(L"Idle");
			float duration = 0.6;
			float step = 0.07;
			CreateClockwiseAnimation(duration, ani);
			bool current = 0;
			for (float i = 0; i <= duration; i += step)
			{
				ani->AddInterpolationKey(i, current);
				current = !current;
			}
			anim->PlayAnimation(L"Idle", true);
		}
		GameObject* burst = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
		MeshRenderer* mr = burst->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"SmallCircle"));
		burst->mTransform->SetScale({ 10, 10, 1 });
		burst->mTransform->SetLocalPosition({ 40, 0, 0 });
	}

	void TutorialBeatBulletsPrefab::Initialize()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"verticlebar"));
		mTransform->SetScale(30, application.GetHeight(), 1);
	}
	
	void TutorialRoundBulletsPrefab::Initialize()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"circle_bullet_prep"));
		mTransform->SetScale(250, 250, 1);
	}

}