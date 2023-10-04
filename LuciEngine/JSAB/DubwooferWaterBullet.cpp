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
	void DubwooferSpikeSingleWave::Initialize()
	{
		Script::Initialize();
		auto mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMr->SetMaterial(Resources::Load<Material>(L"DWWaterMat", L"DB_Water"));
		mMr->GetMaterial()->SetRenderingMode(eRenderingMode::CutOut);

		mTransform->SetScale(40, 0, 1);
		mTime = 0;
		mDuration = 0.55;
		mbWave = false;
		Owner()->SetActive(false);
	}

	void DubwooferSpikeSingleWave::Update()
	{
		if (mbWave)
		{
			double y = 300 + 300 * sin(mTime / mDuration * 2 * PI);
			mTransform->SetScale(mTransform->GetScale().x, y, 1);
			mTime += Time::DeltaTime();
			if (mTime >= mDuration)
			{
				mTime = 0;
				mbWave = false;
				Owner()->SetActive(false);
			}
		}
	}

	void DubwooferSpikeSingleWave::Activate()
	{
		mbWave = true;
		Owner()->SetActive(true);
	}
#pragma endregion


	void DubwooferSpikeWave::Initialize()
	{
		Script::Initialize();
		float startx = 40 * 5 * -0.5;
		for (int i = 0; i < 5; i++)
		{
			float x = startx + 40 * i;
			mWaves[i] = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<DubwooferSpikeSingleWave>();
			mWaves[i]->mTransform->SetLocalPosition(x, 0, 0);
		}

		mAnim = Owner()->AddComponent<Animator>();
		auto anim = mAnim->CreateAnimation(L"Activate");
		anim->AddFunctionKey(0, std::bind(&DubwooferSpikeSingleWave::Activate, mWaves[2]));
		anim->AddFunctionKey(0.15, std::bind(&DubwooferSpikeSingleWave::Activate, mWaves[1]));
		anim->AddFunctionKey(0.15, std::bind(&DubwooferSpikeSingleWave::Activate, mWaves[3]));
		anim->AddFunctionKey(0.3, std::bind(&DubwooferSpikeSingleWave::Activate, mWaves[0]));
		anim->AddFunctionKey(0.3, std::bind(&DubwooferSpikeSingleWave::Activate, mWaves[4]));
		anim->AddPositionKey(1, Vector3::Zero);
	}


	void DubwooferSpikeWave::Activate(Vector3 pos)
	{
		mTransform->SetPosition(pos);
		mAnim->PlayAnimation(L"Activate", false);
	}

}