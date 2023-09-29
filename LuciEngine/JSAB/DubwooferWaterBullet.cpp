#include "DubwooferWaterBullet.h"
#include "DubwooferWater.h"
#include "LGameObject.h"
#include "LMeshRenderer.h"
#include "LCollider2D.h"
#include "LAnimator.h"
#include "LResources.h"
#include "LObject.h"
#include "LTime.h"

namespace lu::JSAB
{
#pragma region Water Bullet
	void DubwooferWaterBullet::Initialize()
	{
		Script::Initialize();
		mAnim = Owner()->AddComponent<Animator>();
		mMr = Owner()->AddComponent<MeshRenderer>();
		mPs = Owner()->AddComponent<ParticleSystem>();
		mCol = Owner()->AddComponent<Collider2D>();

		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMr->SetMaterial(Resources::Load<Material>(L"DWWaterMat", L"DB_Water"));
		mMr->GetMaterial()->SetRenderingMode(eRenderingMode::CutOut);

		mTransform->SetScale(10, 300, 1);
		Owner()->SetTag(eTagType::Bullet);

	}
	void DubwooferWaterBullet::SetY(float y)
	{
		Vector3 currScale = mTransform->GetScale();
		mTransform->SetScale(currScale.x, y, currScale.z);
	}
	void DubwooferWaterBullet::OnCollisionEnter(Collider2D* other)
	{
		if (other->Owner()->GetLayer() == eLayerType::Bullet)
			mBody->OnImpact(mIdx, other->Owner()->mTransform);
	}
#pragma endregion
#pragma region WaterEffect
	void DubwooferSpikeWave::Initialize()
	{
		Script::Initialize();
		auto mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMr->SetMaterial(Resources::Load<Material>(L"DWWaterMat", L"DB_Water"));
		mMr->GetMaterial()->SetRenderingMode(eRenderingMode::CutOut);

		mTransform->SetScale(30, 600, 1);
		mStartTime = 0;
	}

	void DubwooferSpikeWave::Update()
	{
		float cycleDuration = 0.5f; // Total duration of the cycle in seconds

		if (mStartTime < cycleDuration) {
			float y = -2400 / cycleDuration * (mStartTime - cycleDuration * 0.5) * (mStartTime - cycleDuration * 0.5) + 600;

			Vector3 s = mTransform->GetScale();
			s.y = y;
			mTransform->SetScale(s);

			mStartTime += Time::DeltaTime(); // Update the timer based on the frame time
		}
		else
		{
			mStartTime = 0;
		}
	}

#pragma endregion


}