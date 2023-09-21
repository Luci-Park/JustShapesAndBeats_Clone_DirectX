#include "DubwooferBeamBullet.h"
#include "LApplication.h"
#include "LSceneManager.h"
#include "LCamera.h"

extern lu::Application application;
namespace lu::JSAB
{
	void DubwooferBeamBullet::BulletSetUp()
	{
		Vector3 baseScale = { 200, (float)application.GetHeight() * 2, 1 };
		Owner()->SetName(L"Enemy Beam");
		mTransform->SetPosition(Vector3::Up * (float)application.GetHeight() * 0.5);
		mTransform->SetScale(baseScale.x, baseScale.y * 0.5, baseScale.z);

		mCol = Owner()->AddComponent<Collider2D>();

		mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(Resources::Load<Material>(L"EnemyBeamMat", L"verticlebar"));
		mMr->SetColor(Color::white)->UseColor(false);

		mShadow = object::Instantiate<GameObject>(eLayerType::Bullet);
		mShadow->mTransform->SetScale(baseScale);
		
		auto mr = mShadow->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(Resources::Load<Material>(L"EnemyShadowMat", L"verticlebar"));
		mr->GetMaterial()->SetTint({ 1, 1, 1, 0.5 });
		

		mAnim = Owner()->AddComponent<Animator>();
		CreateOnBeatAnimation();
	}
	void DubwooferBeamBullet::OnWarning()
	{
		mMr->SetActive(true);
	}
	void DubwooferBeamBullet::WhileWarning(double time)
	{
		float size = LERP(0, mSize, mWarningProcess);
		Color tint = Color::Lerp({ 0, 0, 0, 0 }, { 1, 1, 1, 0.8 }, mWarningProcess);
		Vector3 scale = mTransform->GetScale();
		scale.x = size;
		mTransform->SetScale(scale);
	}
	void DubwooferBeamBullet::OnActivate()
	{
		mAnim->SetActive(true);
		mAnim->PlayAnimation(L"Activate", false);
	}
	void DubwooferBeamBullet::WhileActivate(double time)
	{
	}
	void DubwooferBeamBullet::OnOutro()
	{
		mAnim->SetActive(true);
		mAnim->PlayAnimation(L"Outro", false);
	}
	void DubwooferBeamBullet::WhileOutro(double time)
	{
	}
	void DubwooferBeamBullet::OnDeActivate()
	{
		//mMr->SetActive(false);
		//mCol->SetActive(false);
		//mAnim->SetActive(false);
		//mShadow->SetActive(false);
	}
	void DubwooferBeamBullet::CreateOnBeatAnimation()
	{
		Vector3 baseScale = { 20, (float)application.GetWidth() * 2, 1 };

		Animation* ani = mAnim->CreateAnimation(L"Activate");
		float flashDur = 0.05;
		ani->AddColliderActiveKey(0, true);
		ani->AddScaleKey(0, { 20, 0, 1 });
		ani->AddInterpolationKey(0, 1);
		ani->AddTintKey(0, Color::white);

		ani->AddScaleKey(flashDur, baseScale);
		ani->AddTintKey(flashDur, Color::white);
		ani->AddInterpolationKey(flashDur, 1);
		ani->AddInterpolationKey(flashDur, 0);
		//ani->AddFunctionKey(flashDur, std::bind(&BeamBullet::CameraShake, this));
		
		float disappearDur = 0.1;
		ani = mAnim->CreateAnimation(L"Outro");
		ani->AddScaleKey(0, baseScale);
		ani->AddScaleKey(disappearDur, { 0, (float)application.GetWidth() * 2, 1 });
		ani->AddFunctionKey(disappearDur, std::bind(&Bullet::DeActivate, this));
	}
	void DubwooferBeamBullet::CameraShake()
	{
		/*
		Quaternion rot = mTransform->GetRotation();
		if (rot == Quaternion::Identity)
			SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect()->Bump(Vector3::Down);
		if (rot == Quaternion::CreateFromAxisAngle(Vector3::Forward, PI))
			SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect()->Bump(Vector3::Up);
		else if (rot == Quaternion::CreateFromAxisAngle(Vector3::Forward, PI * 0.5))
			SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect()->Bump(Vector3::Left);
		else if (rot == Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI * 0.5))
			SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect()->Bump(Vector3::Right);
			*/
	}
}