#include "TryThisSpotlight.h"
#include "LTime.h"
namespace lu::JSAB
{
	void TryThisSpotlight::Update()
	{
		Bullet::Update();
		if (mBulletState != eBulletState::Activate && mBulletState != eBulletState::Outro)
		{
			Move();
			Rotate();
			if (mBulletState == eBulletState::DeActivate)
			{
				mFillTr->SetLocalScale({ 0, 0, 1 });
			}
		}
	}
	void TryThisSpotlight::SetCenter(Vector3 pos)
	{
		mMoveCenter = pos;
		Move();
	}
	void TryThisSpotlight::SetStartAngle(float degrees)
	{
		mAngle = XMConvertToRadians(degrees);
		Move();
	}
	void TryThisSpotlight::BulletSetUp()
	{
		mTransform->SetScale(280, 280, 1);

		auto mesh = Resources::Find<Mesh>(L"RectMesh");
		auto mat = Resources::Load<Material>(L"circle_bullet_prep", L"circle_bullet_prep");
		mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(mesh)->SetMaterial(mat);
		mat->SetRenderingMode(eRenderingMode::CutOut);

		auto fill = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
		fill->SetTag(eTagType::Bullet);

		mFillTr = fill->mTransform;
		mFillTr->SetLocalPosition(0, 0, -0.1);
		mFillMr = fill->AddComponent<MeshRenderer>();
		mFillAnim = fill->AddComponent<Animator>();

		mFillCol = fill->AddComponent<Collider2D>();
		mFillCol->SetType(eColliderType::Circle);

		mat = Resources::Load<Material>(L"SpotlightFill", L"circle_bullet"); 
		mat->SetRenderingMode(eRenderingMode::Transparent);
		mFillMr->SetMesh(mesh)->SetMaterial(mat);
		mFillMr->SetColor(Color::white);

		auto ani = mFillAnim->CreateAnimation(L"Activate");
		float duration = 0.1;
		ani->AddLocalScaleKey(0, { 0, 0, 1 });
		ani->AddLocalScaleKey(duration * 0.8, { 1.3, 1.3, 1 });
		ani->AddLocalScaleKey(duration, { 1.2, 1.2, 1.2 });

		ani = mFillAnim->CreateAnimation(L"Outro");
		duration = 0.1;

		ani->AddLocalScaleKey(0, { 1.2, 1.2, 1 });
		ani->AddLocalScaleKey(duration, { 0, 0, 1 });
		ani->AddFunctionKey(duration, std::bind( & Bullet::DeActivate, this));
		
		RotateClockWise();
		SetStartAngle(0);
		SetCenter(Vector3::Zero);
	}
	void TryThisSpotlight::OnWarning()
	{
		mFillCol->SetActive(false);
		mFillAnim->StopAnimation();
		mFillMr->SetActive(true);
		mFillMr->GetMaterial()->SetTint({ 1, 1, 1, 0.5 });
		mFillMr->UseColor(false);
		mMr->SetActive(true);
	}
	void TryThisSpotlight::WhileWarning(double time)
	{
		Vector3 scale = Vector3::Lerp({ 0, 0, 1 }, { 1, 1, 1 }, mWarningProcess);
		mFillTr->SetLocalScale(scale);

		//Move();
		//Rotate();
	}
	void TryThisSpotlight::OnActivate()
	{
		mFillMr->GetMaterial()->SetTint({ 1, 1, 1, 1 });
		mFillAnim->PlayAnimation(L"Activate", false);
		mFillCol->SetActive(true);
	}
	void TryThisSpotlight::WhileActivate(double time)
	{
	}
	void TryThisSpotlight::OnOutro()
	{
		mFillAnim->PlayAnimation(L"Outro", false);
	}
	void TryThisSpotlight::WhileOutro(double time)
	{
		if(mFillTr->GetLocalScale().x < 0.3)
			Move();
		Rotate();
	}
	void TryThisSpotlight::OnDeActivate()
	{
		//Owner()->SetActive(false);
	}
	void TryThisSpotlight::Move()
	{
		float radius = 200;
		float moveSpeed =
			PI * 0.1;
		mAngle += moveSpeed * Time::DeltaTime();
		Vector3 pos = { cosf(mAngle) * radius, sinf(mAngle) * radius, mTransform->GetPosition().z };
		pos.x += mMoveCenter.x;
		pos.y += mMoveCenter.y;
		mTransform->SetPosition(pos);
	}
	void TryThisSpotlight::Rotate()
	{
		Quaternion speed = Quaternion::CreateFromAxisAngle(Vector3::Forward, mRotSpeed * Time::DeltaTime());
		Quaternion rotation = mTransform->GetRotation();
		mTransform->SetRotation(rotation * speed);
	}
}