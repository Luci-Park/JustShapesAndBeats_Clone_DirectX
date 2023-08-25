#include "TutorialBulletPrefabs.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "LCollider2D.h"
#include "GeneralEffects.h"
#include "LAnimator.h"
#include "LObject.h"
#include "LApplication.h"
#include "TutorialEightBulletScript.h"

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
		ani->AddLocalRotationKey(0, Quaternion::Identity);
		ani->AddLocalRotationKey(duration * .25, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI * 0.5));
		ani->AddLocalRotationKey(duration * .5, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI));
		ani->AddLocalRotationKey(duration * .75, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI * 1.5));
		ani->AddLocalRotationKey(duration, Quaternion::CreateFromAxisAngle(Vector3::Forward, PI * -2));
		anim->PlayAnimation(L"Rotate", true);
		
		CreateEnterEffect(); 
		mTransform->SetScale(Vector3(42, 42, 1));
		AddComponent<Collider2D>()->SetType(eColliderType::Circle);
	}
	void TutorialEightBulletsPrefab::OnEnable()
	{
		mEnterEffect->PlayAnimation(L"Appear", false);
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

		mEnterEffect = anim;
	}

#pragma endregion

#pragma region BurstPrefab
	void TutorialBurstBulletsPrefab::Initialize()
	{
		mTransform->SetScale(Vector3::One);
		BurstScript* script = AddComponent<BurstScript>();
		{
			GameObject* fourSide = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
			fourSide->mTransform->SetLocalScale({ 30, 30, 1 });
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
			fourSide->AddComponent<Collider2D>()->SetType(eColliderType::Circle);
			script->mQuadCircle = fourSide;
			fourSide->SetActive(false);
		}
		float theta = PI * 2 / 8.0f;
		for (int i = 0; i < 8; i++)
		{
			GameObject* burst = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
			MeshRenderer* mr = burst->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"SmallCircle"));
			burst->mTransform->SetScale({ 10, 10, 1 });
			burst->mTransform->SetLocalPosition(Vector3::Zero);
			burst->AddComponent<Collider2D>()->SetType(eColliderType::Circle);
			auto sc = burst->AddComponent<BurstParticleScript>();
			Vector3 dir = { cosf(theta * (float)i), sinf(theta * (float)i) , 0};
			dir.Normalize();
			sc->SetDirection(dir);
			burst->SetActive(false);
			script->mBursts[i] = sc;
		}
		script->DisableBurst();
	}
#pragma endregion

	void TutorialBeatBulletsPrefab::Initialize()
	{
		SetName(L"BarShape");
		mTransform->SetPosition(Vector3::Up * (float)application.GetHeight()*0.5);
		mTransform->SetScale({ 30, (float)application.GetHeight() * 2, 1 });
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"verticlebar"));
		mr->SetColor(Color::white)->UseColor(false);
		AddComponent<Collider2D>()->SetType(eColliderType::Rect)->SetActive(false);
		
		double appearDuration = 0.455;
		double flashDuration = 0.05;
		double stayDuration = 0.1;
		
		Animator* anim = AddComponent<Animator>();
		Animation* ani = anim->CreateAnimation(L"OnBeat");
		ani->AddColliderActiveKey(0, false);
		ani->AddScaleKey(0, { 0, (float)application.GetHeight() * 2, 1 });
		ani->AddTintKey(0, Color::clear);
		ani->AddScaleKey(appearDuration, { 30, (float)application.GetHeight() * 2, 1 });
		ani->AddTintKey(appearDuration, Color::white);

		ani->AddColliderActiveKey(appearDuration, true);		
		ani->AddScaleKey(appearDuration, { 30, 0, 1 });
		ani->AddInterpolationKey(appearDuration, 1);
		ani->AddScaleKey(appearDuration + flashDuration, { 30, (float)application.GetHeight() * 2, 1 });
		ani->AddInterpolationKey(appearDuration + flashDuration, 1);

		ani->AddInterpolationKey(appearDuration + flashDuration, 0);
		ani->AddInterpolationKey(appearDuration + flashDuration + stayDuration, 0);
		ani->AddScaleKey(appearDuration + flashDuration + stayDuration, { 30, (float)application.GetHeight() * 2, 1 });

		anim->PlayAnimation(L"OnBeat", true);
	}
	
	void TutorialRoundBulletsPrefab::Initialize()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"circle_bullet_prep"));
		mTransform->SetScale(250, 250, 1);
	}

}