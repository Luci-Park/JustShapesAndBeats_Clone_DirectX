#include "TryThisLaserBullet.h"
#include "LTime.h"
namespace lu::JSAB
{
#pragma region BasePart

	void TryThisLaserBase::Initialize()
	{
		Script::Initialize();
		Owner()->SetName(L"LaserBase");
		Owner()->SetTag(eTagType::Bullet);
		mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMr->SetMaterial(Resources::Load<Material>(L"TTBaseMat", L"TT_Square"));
		mMr->SetColor(Color::white);

		mAnim = Owner()->AddComponent<Animator>();
		auto anim = mAnim->CreateAnimation(L"Activate");
		anim->AddTintKey(0, Color::white);
		anim->AddInterpolationKey(0, 0);
		anim->AddInterpolationKey(0.1, 1);
		anim->AddInterpolationKey(0.3, 0);

		anim->AddLocalScaleKey(0, { 80, 80, 1 });
		anim->AddLocalScaleKey(0.1, { 40, 40, 1 });
		anim->AddLocalScaleKey(0.3, { 40, 40, 1 });
		anim->AddLocalScaleKey(0.4, { 100, 100, 1 });
	}
	void TryThisLaserBase::Ready()
	{
		mTransform->SetScale(80, 80, 1);
	}
	void TryThisLaserBase::SetAlpha(float alpha)
	{
		mMr->GetMaterial()->SetTint({ 1, 1, 1, alpha });
	}
	void TryThisLaserBase::Activate()
	{
		mAnim->PlayAnimation(L"Activate", false);
	}
#pragma endregion

#pragma region LaserPart

	void TryThisLaserPart::Initialize()
	{
		Script::Initialize();
		Owner()->SetName(L"Laser");
		Owner()->SetTag(eTagType::Bullet);
		mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMr->SetMaterial(Resources::Load<Material>(L"TTLaserMat", L"TT_Square"));
		mMr->SetColor(Color::white);

		mCol = Owner()->AddComponent<Collider2D>();

		mAnim = Owner()->AddComponent<Animator>();
		auto anim = mAnim->CreateAnimation(L"Activate");
		anim->AddColliderActiveKey(0.3, true);
		anim->AddTintKey(0.3, Color::white);
		anim->AddInterpolationKey(0, 0);
		anim->AddInterpolationKey(0.3, 0);
		anim->AddInterpolationKey(0.3, 1);
		anim->AddInterpolationKey(0.4, 0);

		anim->AddLocalScaleKey(0, { 20, 2000, 1 });
		anim->AddLocalScaleKey(0.3, { 20, 2000, 1 });
		anim->AddLocalScaleKey(0.3, { 20, 0, 1 });
		anim->AddLocalScaleKey(0.5, { 20, 2000, 1 });

		anim = mAnim->CreateAnimation(L"DeActivate");
		anim->AddTintKey(0, { 1, 1, 1, 1 });
		anim->AddTintKey(0.3, { 1, 1, 1,  0});
		anim->AddLocalScaleKey(0, { 20, 2000, 1 });
		anim->AddLocalScaleKey(0.3, { 20, 0, 1 });
	}
	void TryThisLaserPart::SetAlpha(float alpha)
	{
		mMr->GetMaterial()->SetTint({ 1, 1, 1, alpha });
	}
	void TryThisLaserPart::Ready()
	{
		mTransform->SetScale(20, 2000, 1);
		mCol->SetActive(false);
	}
	void TryThisLaserPart::Activate()
	{
		mAnim->PlayAnimation(L"Activate", false);
	}
	void TryThisLaserPart::DeActivate()
	{
		mAnim->PlayAnimation(L"DeActivate", false);
	}
#pragma endregion

#pragma region Bullet
	void TryThisLaserBullet::Update()
	{
		Bullet::Update();
		//mRotSpeed = -0.05;
		//WhileActivate(0);
	}
	void TryThisLaserBullet::Shake()
	{
		mOrgPos = mTransform->GetPosition();  
		mbShake = true;
	}
	void TryThisLaserBullet::BulletSetUp()
	{
		Owner()->SetName(L"LaserBullet");
		mAnim = Owner()->AddComponent<Animator>();
		
		auto anim = mAnim->CreateAnimation(L"Deactivate");
		anim->AddScaleKey(0, { 1, 1, 1 });
		anim->AddScaleKey(0.3, { 1, 1, 1 });
		anim->AddScaleKey(0.6, { 0, 0, 1 });

		mBase = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisLaserBase>();
		mLaser1 = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisLaserPart>();
		mLaser2 = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TryThisLaserPart>();
		mBase->mTransform->SetPosition(0, 0, -0.1);
		mLaser1->mTransform->SetRotation(Quaternion::Create2DRotationDegrees(45));
		mLaser2->mTransform->SetRotation(Quaternion::Create2DRotationDegrees(135));
		mBase->Owner()->SetActive(false);
		mLaser1->Owner()->SetActive(false);
		mLaser2->Owner()->SetActive(false);

		mbShake = false;
	}
	void TryThisLaserBullet::OnWarning()
	{
		mTransform->SetScale(1, 1, 1);

		mBase->Owner()->SetActive(true);
		mLaser1->Owner()->SetActive(true);
		mLaser2->Owner()->SetActive(true);

		mBase->Ready();
		mLaser1->Ready();
		mLaser2->Ready();
	}
	void TryThisLaserBullet::WhileWarning(double time)
	{
		float alpha = mWarningProcess * 0.5;
		mBase->SetAlpha(alpha);
		mLaser1->SetAlpha(alpha);
		mLaser2->SetAlpha(alpha);

		Quaternion speed = Quaternion::CreateFromAxisAngle(Vector3::Forward, mRotSpeed * Time::DeltaTime());
		Quaternion rotation = mTransform->GetRotation();
		mTransform->SetRotation(rotation * speed);
	}
	void TryThisLaserBullet::OnActivate()
	{
		mBase->Activate();
		mLaser1->Activate();
		mLaser2->Activate();
		Shake();
	}
	void TryThisLaserBullet::WhileActivate(double time)
	{
		Quaternion speed = Quaternion::CreateFromAxisAngle(Vector3::Forward, mRotSpeed * Time::DeltaTime());
		Quaternion rotation = mTransform->GetRotation();
		mTransform->SetRotation(rotation * speed);
		if (mbShake)
		{
			Vector3 pos = mOrgPos + RandomInsideUnitCircle() * 2;
			mTransform->SetPosition(pos);
		}
	}
	void TryThisLaserBullet::OnOutro()
	{
		mLaser1->DeActivate();
		mLaser2->DeActivate();
		mAnim->PlayAnimation(L"Deactivate", false);
		mbShake = false;
	}
	void TryThisLaserBullet::WhileOutro(double time)
	{
		Quaternion speed = Quaternion::CreateFromAxisAngle(Vector3::Forward, mRotSpeed * Time::DeltaTime());
		Quaternion rotation = mTransform->GetRotation();
		mTransform->SetRotation(rotation * speed);
	}
	void TryThisLaserBullet::OnDeActivate()
	{
		mBase->Owner()->SetActive(false);
		mLaser1->Owner()->SetActive(false);
		mLaser2->Owner()->SetActive(false);
	}
#pragma endregion
}