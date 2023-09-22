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

		Vector3 scale = { 100, 100, 1 };
		mTransform->SetScale(scale);
		mTransform->SetRotation(Quaternion::Create2DRotationDegrees(180));

		auto g = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
		g->SetTag(eTagType::Bullet);
		g->AddComponent<Collider2D>();

		mRb = g->AddComponent<Rigidbody>();
		mRb->SetMass(100);
		mRb->UseGravity(false);

		auto mr = g->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Load<Material>(L"DWSpikeMat", L"DB_Ceiling"));
		mr->GetMaterial()->SetRenderingMode(eRenderingMode::Transparent);
		mr->SetColor(Color::white);

		float px = scale.x * 0.5;
		float py = scale.y * 0.5;
		float theta = XMConvertToRadians(160);

		mSpikeAnim = g->AddComponent<Animator>();
		auto ani = mSpikeAnim->CreateAnimation(L"Fall");
		float duration = 0.2;	
		ani->AddRotationKey(0, Quaternion::Create2DRotationDegrees(180));
		ani->AddRotationKey(duration, Quaternion::Create2DRotationRadian(theta));
		ani->AddLocalPositionKey(0, Vector3::Zero);
		//ani->AddLocalPositionKey(duration, { -9.43f, -9.67f, 0 });
		ani->AddLocalPositionKey(duration, {cosf(theta) * px + sinf(theta) * py, sinf(theta) * px + cosf(theta) * py + 20, 0});
		ani->AddInterpolationKey(0, 0);
		ani->AddInterpolationKey(duration* 0.25, 1);
		ani->AddInterpolationKey(duration* 0.5, 0);
		ani->AddInterpolationKey(duration* 0.75, 1);
		ani->AddInterpolationKey(duration* 1, 0);

		ani = mSpikeAnim->CreateAnimation(L"OnImpact");
		duration = 0.1;
		ani->AddLocalPositionKey(0, { 0, 0, 0 });
		ani->AddLocalPositionKey(duration * 0.5, { 0, -10, 0 });
		ani->AddLocalPositionKey(duration, { 0, -10, 0 });
	}
	void DubwooferSpikeBullet::Reset()
	{ 
		mRb->UseGravity(false);
	}
	void DubwooferSpikeBullet::Activate()
	{
		mRb->UseGravity(true);
		mRb->SetVelocity(Vector3::Zero);
		mSpikeAnim->PlayAnimation(L"Fall", false);
	}
}