#include "DubwooferSpikeBullet.h"
#include "LGameObject.h"
#include "LMeshRenderer.h"
#include "LCollider2D.h"
#include "LAnimator.h"
#include "LResources.h"
#include "LRigidBody.h"
#include "LObject.h"
namespace lu::JSAB
{
	void DubwooferSpikeBullet::Initialize()
	{
		Script::Initialize();
		float width = 60.f;

		Owner()->SetTag(eTagType::Bullet);
		auto mr = Owner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Load<Material>(L"DWSpikeMat", L"DB_Ceiling"));
		mr->GetMaterial()->SetRenderingMode(eRenderingMode::CutOut);
		auto tex = mr->GetMaterial()->GetTexture();
		mTransform->SetScale(110, 100, 1);
		mTransform->SetRotation(Quaternion::Create2DRotationDegrees(180));

		Owner()->AddComponent<Collider2D>();
		mBaseAnim = Owner()->AddComponent<Animator>();
		mRb = Owner()->AddComponent<Rigidbody>();

		auto g = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
		mr = g->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Load<Material>(L"DWSpikeHoleMat", L"DB_CeilingHole"));
		mr->GetMaterial()->SetRenderingMode(eRenderingMode::Transparent);
		mr->SetColor(Color::white);

		g->mTransform->SetLocalPosition(0, 0, 0.1);
		mHoleAnim = g->AddComponent<Animator>();		

		auto ani = mHoleAnim->CreateAnimation(L"Flash");
		float duration = 0.3;
		ani->AddInterpolationKey(0, 0);
		ani->AddInterpolationKey(duration * 0.5, 1);
		ani->AddInterpolationKey(duration, 0);
		
		ani = mBaseAnim->CreateAnimation(L"Fall");
		duration = 0.5;
		ani->AddLocalPositionYKey(0, 0);
		ani->AddLocalPositionXKey(0, 0);
		ani->AddRotationKey(0, Quaternion::Create2DRotationDegrees(180));
		ani->AddRotationKey(0.1, Quaternion::Create2DRotationDegrees(180 - 30));
		ani->AddLocalPositionYKey(0.1, -10);

	}
	void DubwooferSpikeBullet::Reset()
	{
	}
	void DubwooferSpikeBullet::Activate()
	{
		mBaseAnim->PlayAnimation(L"Fall", false);
	}
}