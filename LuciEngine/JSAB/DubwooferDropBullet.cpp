#include "DubwooferDropBullet.h"
#include "LGameObject.h"
#include "LMeshRenderer.h"
#include "LCollider2D.h"
#include "LAnimator.h"
#include "LResources.h"
#include "LRigidBody.h"
#include "LParticleSystem.h"

#include "LInput.h"
namespace lu::JSAB
{
	DubwooferDropBullet::DubwooferDropBullet()
		: mAnim(nullptr)
	{
	}
	void DubwooferDropBullet::Initialize()
	{
		Script::Initialize();
		mTransform->SetScale({ 15, 15, 1 });
		mTransform->SetPosition({ 0, 0, -20 });
		Owner()->SetTag(eTagType::Bullet);
		Owner()->AddComponent<Collider2D>()->SetType(eColliderType::Circle);
		
		auto mr = Owner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))
			->SetMaterial(Resources::Load<Material>(L"DropBulletMat", L"SmallCircle"));
		mr->GetMaterial()->SetRenderingMode(eRenderingMode::CutOut);
		mAnim = Owner()->AddComponent<Animator>();
		auto ani = mAnim->CreateAnimation(L"Drop");
		float dur = 0.5;
		ani->AddScaleKey(dur * 0, { 3, 27, 1 });
		ani->AddScaleKey(dur *0.25, { 24, 6, 1 });
		ani->AddScaleKey(dur *0.5, { 10, 20, 1 });
		ani->AddScaleKey(dur * 0.75, { 18, 12, 1 });
		ani->AddScaleKey(dur * 1, { 15, 15, 1 });

		mRb = Owner()->AddComponent<Rigidbody>();
		mRb->UseGravity(false);

		mParticle = Owner()->AddComponent<ParticleSystem>();
		mParticle->Duration = 3;
		mParticle->Loop = false;
		mParticle->RateOverTime = 0;
		mParticle->RateOverDistance = 0;
		mParticle->Bursts.push_back({0, 5, false});
		mParticle->SetTexture(Resources::Find<Texture>(L"SmallCircle"));
		mParticle->SetLifeTime(0.5);
		mParticle->SetSize(10, 0);
		mParticle->SetStartSpeed(0);
		mParticle->SetStartRadius(0);
		mParticle->SetAngle(-180, 0);
		mParticle->SetGravity(300);
	}
	void DubwooferDropBullet::Update()
	{
	}
	void DubwooferDropBullet::Activate()
	{
		Owner()->SetActive(true);
		mRb->SetVelocity(Vector3::Down * 350);
		mRb->UseGravity(true);
		mAnim->PlayAnimation(L"Drop", false);
		mParticle->Play();
	}
	void DubwooferDropBullet::DeActivate()
	{
		Owner()->SetActive(false);
	}
}