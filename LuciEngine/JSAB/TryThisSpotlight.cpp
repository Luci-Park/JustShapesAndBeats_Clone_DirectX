#include "TryThisSpotlight.h"
#include "LTime.h"
namespace lu::JSAB
{
	void TryThisSpotlight::Update()
	{
		//static float time = 0;
		Bullet::Update();
		//mWarningProcess = time / 5;
		//time += Time::DeltaTime();
		//if (time > 1)
		//	time = 0;
		//WhileWarning(0);
	}
	void TryThisSpotlight::BulletSetUp()
	{
		mTransform->SetScale(230, 230, 1);

		auto mesh = Resources::Find<Mesh>(L"RectMesh");
		auto mat = Resources::Load<Material>(L"circle_bullet_prep", L"circle_bullet_prep");
		mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(mesh)->SetMaterial(mat);
		mat->SetRenderingMode(eRenderingMode::CutOut);

		auto fill = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
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
		ani->AddLocalScaleKey(duration, { 1.1, 1.1, 1.1 });
		
		RotateClockWise();
	}
	void TryThisSpotlight::OnWarning()
	{
		mFillCol->SetActive(false);
		mFillAnim->StopAnimation();
		mFillMr->SetActive(true);
		mFillMr->GetMaterial()->SetTint({ 1, 1, 1, 0.5 });
		mFillMr->UseColor(false);
		mMr->SetActive(true);
		mFillTr->SetLocalScale(0.5, 0.5, 1);
	}
	void TryThisSpotlight::WhileWarning(double time)
	{
		//Vector3 scale = Vector3::Lerp({ 0, 0, 1 }, { 1, 1, 1 }, mWarningProcess);
		//mFillTr->SetLocalScale(scale);

		Quaternion speed = Quaternion::CreateFromAxisAngle(Vector3::Forward, mRotSpeed * Time::DeltaTime());
		Quaternion rotation = mTransform->GetRotation();
		mTransform->SetRotation(rotation * speed);
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
	}
	void TryThisSpotlight::WhileOutro(double time)
	{
	}
	void TryThisSpotlight::OnDeActivate()
	{
		//mFillCol->SetActive(false);
		//mFillMr->Owner()->SetActive(false);
		//mMr->SetActive(false);
	}
}