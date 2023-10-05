#include "TryThisRoundSpike.h"
#include "LTime.h"
namespace lu::JSAB
{
	void TryThisRoundSpike::Setup(Vector3 dir, bool clockwise)
	{
		mMoveSpeed = 0.4;
		mMoveDir = dir;
		if (clockwise)
			mRotateSpeed = -0.4;
		else
			mRotateSpeed = 0.4;
	}
	void TryThisRoundSpike::BulletSetUp()
	{
		Owner()->SetName(L"FourPointBullet");
		mTransform->SetScale(Vector3(42, 42, 1));
		mCol = Owner()->AddComponent<Collider2D>()->SetType(eColliderType::Circle);

		auto mat = Resources::Load<Material>(L"FourPointMat", L"TT_Star");

		mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(mat);

		CreateEnterEffect();
	}
	void TryThisRoundSpike::OnWarning()
	{
	}
	void TryThisRoundSpike::WhileWarning(double time)
	{
	}
	void TryThisRoundSpike::OnActivate()
	{
		mEnterEffect->Owner()->SetActive(true);
		mMr->SetActive(true);
		mCol->SetActive(true);
		mEnterEffect->PlayAnimation(L"Appear", false);
	}
	void TryThisRoundSpike::WhileActivate(double time)
	{
		Quaternion speed = Quaternion::CreateFromAxisAngle(Vector3::Forward, mRotateSpeed * Time::DeltaTime());
		Quaternion rotation = mTransform->GetRotation();
		mTransform->SetRotation(rotation * speed);

		Vector3 movePos = mMoveSpeed * mMoveDir * Time::DeltaTime();
		mTransform->SetPosition(mTransform->GetPosition() + movePos);

		Rectangle bBound = { (long)mTransform->GetPosition().x,(long)mTransform->GetPosition().y, (long)mTransform->GetScale().x, (long)mTransform->GetScale().y };
		if (!((Rectangle)mBounds).Contains(bBound))
			DeActivate();
	}
	void TryThisRoundSpike::OnOutro()
	{
	}
	void TryThisRoundSpike::WhileOutro(double time)
	{
	}
	void TryThisRoundSpike::OnDeActivate()
	{
		mEnterEffect->Owner()->SetActive(false);
		mMr->SetActive(false);
		mCol->SetActive(false);
	}
	void TryThisRoundSpike::CreateEnterEffect()
	{
		GameObject* enterEffect = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
		enterEffect->SetName(L"enterburst");
		enterEffect->mTransform->SetLocalPosition({ 0, 0, -0.1 });

		MeshRenderer* mr = enterEffect->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(Resources::Load<Material>(L"circle_bullet_blink_white", L"circle_bullet_blink_white"));

		Animator* anim = enterEffect->AddComponent<Animator>();
		Animation* ani = anim->CreateAnimation(L"Appear");
		float duration = 0.5;
		ani->AddTintKey(0, Color::white);
		ani->AddTintKey(duration, { 1, 1, 1, 0 });
		ani->AddLocalScaleKey(0, { 0, 0, 1 });
		ani->AddLocalScaleKey(0.1, { 1, 1, 1 });
		ani->AddLocalScaleKey(duration, { 0, 0, 1 });

		mEnterEffect = anim;
	}
}