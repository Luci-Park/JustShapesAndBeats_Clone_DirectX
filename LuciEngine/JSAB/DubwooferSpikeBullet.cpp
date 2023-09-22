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

		mTransform->SetScale(100, 100, 1);
		mTransform->SetRotation(Quaternion::Create2DRotationDegrees(180));

		auto g = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
		g->SetTag(eTagType::Bullet);
		g->AddComponent<Collider2D>();
		mSpikeAnim = g->AddComponent<Animator>();
		mRb = g->AddComponent<Rigidbody>();

		auto mr = g->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Load<Material>(L"DWSpikeMat", L"DB_Ceiling"));
		mr->GetMaterial()->SetRenderingMode(eRenderingMode::Transparent);
		mr->SetColor(Color::white);

		float px = 25 * -1.5f;
		float py = 25 * 1.5f;
		auto ani = mSpikeAnim->CreateAnimation(L"Fall");
		float duration = 0.2;
		ani->AddRotationKey(0, Quaternion::Create2DRotationDegrees(180));
		ani->AddRotationKey(duration, Quaternion::Create2DRotationDegrees(180 - 20));
		ani->AddLocalPositionKey(0, Vector3::Zero);
		ani->AddLocalPositionKey(duration, { -9.43f, -9.67f, 0 });
		ani->AddInterpolationKey(0, 0);
		ani->AddInterpolationKey(duration* 0.25, 1);
		ani->AddInterpolationKey(duration* 0.5, 0);
		ani->AddInterpolationKey(duration* 0.75, 1);
		ani->AddInterpolationKey(duration* 1, 0);

	}
	void DubwooferSpikeBullet::Reset()
	{ 
	}
	void DubwooferSpikeBullet::Activate()
	{
		mSpikeAnim->PlayAnimation(L"Fall", false);
	}
}