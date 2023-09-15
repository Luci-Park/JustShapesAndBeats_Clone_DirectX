#include "EnemyCircle.h"
namespace lu::JSAB
{
	void EnemyCircle::BulletSetUp()
	{
		Owner()->SetName(L"BeatCircle");
		mTransform->SetLocalScale({ 230, 230, 1 });
		mCol = Owner()->AddComponent<Collider2D>()->SetType(eColliderType::Circle);

		mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))
			->SetMaterial(Resources::Load<Material>(L"BeatCircleMat", L"circle_bullet_prep"));
		mMr->SetColor(Color::white)->UseColor(false);

		mReadySprite = Resources::Find<Texture>(L"circle_bullet_prep");
		mActivateSprite = Resources::Find<Texture>(L"circle_bullet");

		mAnim = Owner()->AddComponent<Animator>();
		CreateAnimation();
	}
	void EnemyCircle::OnDeActivate()
	{
		mAnim->SetActive(false);
		mMr->SetActive(false);
		mCol->SetActive(false);
	}
	void EnemyCircle::OnWarning()
	{
		mAnim->SetActive(true);
		mMr->SetActive(true);
		mAnim->PlayAnimation(L"Warning", true);
	}
	void EnemyCircle::WhileWarning(double time)
	{
	}
	void EnemyCircle::OnActivate()
	{
		mCol->SetActive(true);
		mAnim->PlayAnimation(L"MoveCircle", true);
		mMr->GetMaterial()->SetTexture(mActivateSprite);
	}
	void EnemyCircle::WhileActivate(double time)
	{
	}
	void EnemyCircle::OnOutro()
	{
	}
	void EnemyCircle::WhileOutro(double time)
	{
	}
	void EnemyCircle::CreateAnimation()
	{
		auto ani = mAnim->CreateAnimation(L"MoveCircle");
		float duration = 0.5;
		int iSlice = 40;
		float fRadius = 5.f;
		float fTheta = XM_2PI / (float)iSlice;
		float fdur = duration / (float)iSlice;
		for (int i = 0; i < iSlice; ++i)
		{
			Vector3 pos = Vector3(fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, 0.0f);
			ani->AddPositionKey(fdur * (float)i, pos);
		}

		ani = mAnim->CreateAnimation(L"Warning");
		ani->AddTextureKey(0, mReadySprite);
		ani->AddLocalRotationKey(0, Quaternion::Identity);
		ani->AddLocalRotationKey(duration * .25, Quaternion::CreateFromAxisAngle(Vector3::Forward, PI * 0.5));
		ani->AddLocalRotationKey(duration * .5, Quaternion::CreateFromAxisAngle(Vector3::Forward, PI));
		ani->AddLocalRotationKey(duration * .75, Quaternion::CreateFromAxisAngle(Vector3::Forward, PI * 1.5));
		ani->AddLocalRotationKey(duration, Quaternion::CreateFromAxisAngle(Vector3::Forward, PI * 2));
	}
}