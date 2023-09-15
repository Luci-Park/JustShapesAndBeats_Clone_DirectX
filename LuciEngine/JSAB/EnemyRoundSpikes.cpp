#include "EnemyRoundSpikes.h"
#include "LSceneManager.h"
#include "LTime.h"
namespace lu::JSAB
{
	void EnemyRoundSpikes::SetPosition(Vector3 mStart, Vector3 mEnd)
	{
		mStartPos = mStart;
		mEndPos = mEnd;
	}
	void EnemyRoundSpikes::BulletSetUp()
	{
		Owner()->SetName(L"EightRoundSpikes");
		mTransform->SetScale(Vector3(42, 42, 1));
		Owner()->AddComponent<Collider2D>()->SetType(eColliderType::Circle);
		mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMr->SetMaterial(Resources::Load<Material>(L"EightRoundSpikesMat", L"octa_circle_bullet"));

		{
			GameObject* enterEffect = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
			enterEffect->SetName(L"Enterburst");
			enterEffect->mTransform->SetLocalPosition({ 0, 0, -0.1 });

			MeshRenderer* mr = enterEffect->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))
				->SetMaterial(Resources::Load<Material>(L"EnterBurstMat", L"circle_bullet_blink_white"));

			Animator* anim = enterEffect->AddComponent<Animator>();
			Animation* ani = anim->CreateAnimation(L"Appear");
			float duration = 0.7;
			ani->AddTintKey(0, Color::white);
			ani->AddTintKey(duration, { 1, 1, 1, 0 });
			ani->AddLocalScaleKey(0, { 0, 0, 1 });
			ani->AddLocalScaleKey(0.2, { 1, 1, 1 });
			ani->AddLocalScaleKey(duration, { 0, 0, 1 });

			mEnterEffect = anim;
		}
		mRotateSpeed = PI * -2;
	}
	void EnemyRoundSpikes::OnActivate()
	{
		mEnterEffect->Owner()->SetActive(true);
		mMr->SetActive(true);
		mEnterEffect->PlayAnimation(L"Appear", false);
	}
	void EnemyRoundSpikes::WhileActivate(double time)
	{
		mMoveTime += Time::DeltaTime();
		Vector3 rot = mTransform->GetRotation().ToEuler();
		rot.z += mRotateSpeed * Time::DeltaTime();
		mTransform->SetRotation(Quaternion::CreateFromYawPitchRoll(rot));
		if (mStartPos == mEndPos) return;
		float t = mMoveTime / 7;
		if (t > 1)
		{
			mMoveTime = 0;
			DeActivate();
		}
		mTransform->SetPosition(Vector3::Lerp(mStartPos, mEndPos, t));
	}
	void EnemyRoundSpikes::OnDeActivate()
	{
		mEnterEffect->Owner()->SetActive(false);
		mMr->SetActive(false);
		mTransform->SetPosition(mStartPos);
		mMoveTime = 0;
	}
}