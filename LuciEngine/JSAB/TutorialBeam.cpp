#include "TutorialBeam.h"
#include "GeneralEffects.h"
#include "LApplication.h"
#include "LTime.h"
#include "LRenderer.h"

extern lu::Application application;
namespace lu::JSAB
{
	void TutorialBeam::SetRandomPosition()
	{
		int y = lu::math::IntRandom(0, 1);
		Vector3 pos;
		Quaternion rot;
		if (y)
		{
			int up = lu::math::IntRandom(0, 1);
			pos = (up ? Vector3::Up : Vector3::Down) * application.GetHeight() * 0.5f;
			rot = up ? Quaternion::Identity : Quaternion::CreateFromAxisAngle(Vector3::Forward, PI);
			pos.x = lu::math::RealRandom<float>(application.GetWidth() * -0.5f, application.GetWidth() * 0.5f);
		}
		else
		{
			int left = lu::math::IntRandom(0, 1);
			pos = (left ? Vector3::Left : Vector3::Right) * application.GetWidth() * 0.5f;
			rot = left ? Quaternion::CreateFromAxisAngle(Vector3::Forward, PI * 0.5) : Quaternion::CreateFromAxisAngle(Vector3::Forward, PI * -0.5);
			pos.y = lu::math::RealRandom<float>(application.GetHeight() * -0.5f, application.GetHeight() * 0.5f);
		}
		mTransform->SetPosition(pos);
		mTransform->SetRotation(rot);
	}
	void TutorialBeam::SetSize(float x)
	{
		mXSize = x;
		Vector3 scale = mTransform->GetScale();
		scale.x = x;
		mTransform->SetScale(scale);
	}
	void TutorialBeam::BulletSetUp()
	{
		mXSize = 20;
		Vector3 baseScale = { 20, (float)application.GetWidth() * 2, 1 };
		Owner()->SetName(L"Tutorial Enemy Beam");
		mTransform->SetPosition(Vector3::Up * (float)application.GetHeight() * 0.5);
		mTransform->SetScale(baseScale);

		mCol = Owner()->AddComponent<Collider2D>();

		mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"verticlebar"));
		mMr->SetColor(Color::white)->UseColor(false);

		mAnim = Owner()->AddComponent<Animator>();
		CreateOnBeatAnimation();
	}
	void TutorialBeam::OnWarning()
	{
		mMr->SetActive(true);
		mAnim->SetActive(true);
		//mAnim->PlayAnimation(L"Warning", false);
	}
	void TutorialBeam::WhileWarning(double time)
	{
		float size = LERP(0, mXSize, mWarningProcess);
		Vector3 scale = mTransform->GetScale();
		scale.x = size;
		mTransform->SetScale(scale);

		Color tint = Color::Lerp({ 0, 0, 0, 0 }, { 1, 1, 1, 0.8 }, mWarningProcess);
		mMr->GetMaterial()->SetTint(tint);
	}
	void TutorialBeam::OnActivate()
	{
		mMr->SetActive(true);
		mAnim->SetActive(true);
		mCol->SetActive(true);
		mAnim->PlayAnimation(L"Activate", false);
	}
	void TutorialBeam::WhileActivate(double time)
	{
	}
	void TutorialBeam::OnOutro()
	{
		mAnim->PlayAnimation(L"Outro", false);
	}
	void TutorialBeam::WhileOutro(double time)
	{
	}
	void TutorialBeam::OnDeActivate()
	{
		mMr->SetActive(false);
		mCol->SetActive(false);
		mAnim->SetActive(false);
	}
	void TutorialBeam::CreateOnBeatAnimation()
	{
		Vector3 baseScale = { 20, (float)application.GetWidth() * 2, 1 };

		Animation* ani = mAnim->CreateAnimation(L"Warning");
		ani->AddScaleKey(0, { 0, (float)application.GetWidth() * 2, 1 });
		ani->AddTintKey(0, Color::clear);
		ani->AddScaleKey(appearDuration, baseScale);
		ani->AddTintKey(appearDuration, {1.f, 1.f, 1.f, 0.8f});

		ani = mAnim->CreateAnimation(L"Activate");
		ani->AddColliderActiveKey(0, true);
		ani->AddTrScaleYKey(0, 0);
		ani->AddInterpolationKey(0, 1);
		ani->AddTintKey(0, Color::white);

		ani->AddTrScaleYKey(flashDuration, baseScale.y);
		ani->AddTintKey(flashDuration, Color::white);
		ani->AddInterpolationKey(flashDuration, 1);
		ani->AddInterpolationKey(flashDuration, 0);

		ani->AddFunctionKey(flashDuration, std::bind(&TutorialBeam::Beat, this));

		ani = mAnim->CreateAnimation(L"Outro");
		ani->AddScaleKey(0, baseScale);
		ani->AddScaleKey(disappearDuration, { 0, (float)application.GetWidth() * 2, 1 });
		ani->AddFunctionKey(disappearDuration, std::bind(&Bullet::DeActivate, this));
	}
	void TutorialBeam::Beat()
	{
		Quaternion rot = mTransform->GetRotation();
		if(rot == Quaternion::Identity)
			SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect()->Bump(Vector3::Down);
		if (rot == Quaternion::CreateFromAxisAngle(Vector3::Forward, PI))
			SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect()->Bump(Vector3::Up);
		else if (rot == Quaternion::CreateFromAxisAngle(Vector3::Forward, PI*0.5))
			SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect()->Bump(Vector3::Left);
		else if (rot == Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI * 0.5))
			SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect()->Bump(Vector3::Right);
	}
}