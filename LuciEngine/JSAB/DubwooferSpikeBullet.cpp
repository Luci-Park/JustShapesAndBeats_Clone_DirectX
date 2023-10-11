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
		Owner()->SetName(L"SpikeBulletParent");
		Owner()->SetTag(eTagType::Bullet);

		Vector3 scale = { 100, 100, 1 };
		mTransform->SetScale(scale);
		mTransform->SetRotation(Quaternion::Create2DRotationDegrees(180));

		mSpike = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
		mSpike->SetTag(eTagType::Bullet);
		mSpike->AddComponent<Collider2D>();
		mSpike->SetName(L"SpikeBullet");

		mRb = mSpike->AddComponent<Rigidbody>();
		mRb->SetMass(100);
		mRb->UseGravity(false);

		auto mr = mSpike->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Load<Material>(L"DWSpikeMat", L"DB_Ceiling"));
		mr->GetMaterial()->SetRenderingMode(eRenderingMode::Transparent);
		mr->SetColor(Color::white);

		float px = scale.x * 0.5;
		float py = scale.y * 0.5;
		float theta = XMConvertToRadians(160);

		mSpikeAnim = mSpike->AddComponent<Animator>();
		auto ani = mSpikeAnim->CreateAnimation(L"Fall");
		float duration = 0.2;	
		ani->AddRotationKey(0, Quaternion::Create2DRotationDegrees(180));
		ani->AddRotationKey(duration, Quaternion::Create2DRotationRadian(theta));
		ani->AddLocalPositionKey(0, Vector3::Zero);

		ani->AddLocalPositionKey(duration, {cosf(theta) * px + sinf(theta) * py, sinf(theta) * px + cosf(theta) * py + 20, 0});
		ani->AddInterpolationKey(0, 0);
		ani->AddInterpolationKey(duration* 0.25, 1);
		ani->AddInterpolationKey(duration* 0.5, 0);
		ani->AddInterpolationKey(duration* 0.75, 1);
		ani->AddInterpolationKey(duration* 1, 0);
		ani->AddFunctionKey(0.55, std::bind(&Rigidbody::UseGravity, mRb, true));
		ani->AddFunctionKey(0.55, std::bind(&Rigidbody::SetVelocity, mRb, Vector3::Zero));
		ani->AddFunctionKey(0.55 * 3, std::bind(&DubwooferSpikeBullet::Reset, this));

		ani = mSpikeAnim->CreateAnimation(L"Shake");
		duration = 0.1;
		ani->AddLocalPositionKey(0, { 0, 0, 0 });
		ani->AddLocalPositionKey(duration * 0.25, { -10, 0, 0 });
		ani->AddLocalPositionKey(duration *0.5, { 8, 0, 0 });
		ani->AddLocalPositionKey(duration *0.75, { -3, 0, 0 });
		ani->AddLocalPositionKey(duration, { 0, 0, 0 });

		ani = mSpikeAnim->CreateAnimation(L"Reset");
		duration = 0.3;
		ani->AddLocalPositionKey(0, { 0, 60, 0 });
		ani->AddLocalPositionKey(duration, { 0, 0, 0 });

		mSpike->mTransform->SetLocalPosition(Vector3::Zero);
	}
	void DubwooferSpikeBullet::Reset()
	{ 		
		mRb->UseGravity(false);
		mRb->SetVelocity(Vector3::Zero);
		mRb->Owner()->mTransform->SetRotation(Quaternion::Create2DRotationDegrees(180));
		mSpikeAnim->PlayAnimation(L"Reset", false);
	}
	void DubwooferSpikeBullet::Activate()
	{
		mSpikeAnim->PlayAnimation(L"Fall", false);
	}
	void DubwooferSpikeBullet::Shake()
	{
		if(!mSpikeAnim->IsPlaying())
			mSpikeAnim->PlayAnimation(L"Shake", false);
	}
}