#include "EnemyBeam.h"
#include "LApplication.h"

extern lu::Application application;
namespace lu::JSAB
{
	void EnemyBeam::BulletSetUp()
	{
		Vector3 baseScale = { 20, (float)application.GetWidth() * 2, 1 };
		Owner()->SetName(L"BeatBar");
		mTransform->SetPosition(Vector3::Up * (float)application.GetHeight() * 0.5);
		mTransform->SetScale(baseScale);

		mCol = Owner()->AddComponent<Collider2D>();

		mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(Resources::Load<Material>(L"BarMat", L"verticlebar"));
		mMr->SetColor(Color::white)->UseColor(false);
		
		mAnim = Owner()->AddComponent<Animator>();
		CreateOnBeatAnimation();
	}
	void EnemyBeam::OnDeActivate()
	{
		mMr->SetActive(false);
		mCol->SetActive(false);
		mAnim->SetActive(false);
	}
	void EnemyBeam::OnWarning()
	{
		mMr->SetActive(true);
		mAnim->SetActive(true);
		mAnim->PlayAnimation(L"Warning", false);
	}
	void EnemyBeam::WhileWarning(double time)
	{
	}
	void EnemyBeam::OnActivate()
	{
		mAnim->PlayAnimation(L"Appear", false);
		mCol->Active(true);
	}
	void EnemyBeam::WhileActivate(double time)
	{
	}
	void EnemyBeam::OnOutro()
	{
		mAnim->PlayAnimation(L"Disappear", false);
	}
	void EnemyBeam::WhileOutro(double time)
	{
	}
	void EnemyBeam::CreateOnBeatAnimation()
	{
		Vector3 baseScale = { 20, (float)application.GetWidth() * 2, 1 };

		Animation* ani = mAnim->CreateAnimation(L"Warning");
		ani->AddScaleKey(0, { 0, (float)application.GetWidth() * 2, 1 });
		ani->AddTintKey(0, Color::clear);
		ani->AddScaleKey(1.52, baseScale);
		ani->AddTintKey(1.52, { 1.f, 1.f, 1.f, 0.8f });

		ani = mAnim->CreateAnimation(L"Appear");
		ani->AddScaleKey(0, { 20, 0, 1 });
		ani->AddInterpolationKey(0, 1);
		ani->AddTintKey(0, Color::white);

		ani->AddScaleKey(0.05, baseScale);
		ani->AddTintKey(0.05, Color::white);
		ani->AddInterpolationKey(0.05, 1);
		ani->AddInterpolationKey(0.05, 0);

		ani->AddFunctionKey(0.05, std::bind(&EnemyBeam::Beat, this));

		ani = mAnim->CreateAnimation(L"Disappear");
		ani->AddScaleKey(0, baseScale);
		ani->AddScaleKey(0.35, { 0, (float)application.GetWidth() * 2, 1 });
	}
	void EnemyBeam::Beat()
	{
		Quaternion rot = mTransform->GetRotation();
		if (rot == Quaternion::Identity)
			mCamera->Bump(Vector3::Down);
		if (rot == Quaternion::CreateFromAxisAngle(Vector3::Forward, PI))
			mCamera->Bump(Vector3::Up);
		else if (rot == Quaternion::CreateFromAxisAngle(Vector3::Forward, PI * 0.5))
			//position = { -application.GetWidth() * 0.5f,0, 0);
			mCamera->Bump(Vector3::Left);
		//position = { application.GetWidth() * 0.5f,0, 0);
		else if (rot == Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI * 0.5))
			mCamera->Bump(Vector3::Right);
	}
}