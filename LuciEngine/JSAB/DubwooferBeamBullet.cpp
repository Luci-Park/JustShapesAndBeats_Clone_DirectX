#include "DubwooferBeamBullet.h"
#include "LApplication.h"
#include "LSceneManager.h"
#include "LCamera.h"

extern lu::Application application;
namespace lu::JSAB
{
	void DubwooferBeamBullet::SetSize(float x)
	{
		mSize = x;
		Vector3 scale = mTransform->GetScale();
		scale.x = x;
		mTransform->SetScale(scale);
	}
	void DubwooferBeamBullet::BulletSetUp()
	{
		mSize = 200;
		Vector3 baseScale = { mSize, (float)application.GetWidth() * 2, 1 };
		Owner()->SetName(L"Dubwoofer Enemy Beam");
		mTransform->SetPosition(0, (float)application.GetHeight() * 0.5, 2);
		mTransform->SetScale(baseScale.x, baseScale.y * 0.5, baseScale.z);

		mCol = Owner()->AddComponent<Collider2D>();

		mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(Resources::Load<Material>(L"EnemyBeamMat", L"verticlebar"));
		mMr->GetMaterial()->SetRenderingMode(eRenderingMode::Opaque);
		mMr->SetColor(Color::white)->UseColor(false);

		mShadow = object::Instantiate<GameObject>(eLayerType::Bullet);
		mShadow->mTransform->SetScale(baseScale);
		mShadow->mTransform->SetPosition(0, 0, 2.1);
		
		auto mr = mShadow->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(Resources::Load<Material>(L"EnemyShadowMat", L"verticlebar"));
		mr->GetMaterial()->SetRenderingMode(eRenderingMode::Transparent);
		mr->GetMaterial()->SetTint({ 1, 1, 1, 0.5 });

		mAnim = Owner()->AddComponent<Animator>();
		CreateOnBeatAnimation();
	}
	void DubwooferBeamBullet::OnWarning()
	{
		Vector3 scale = mTransform->GetScale();
		scale.x = mSize;
		mTransform->SetScale(scale);

		mShadow->mTransform->SetPosition(mTransform->GetPosition());
		scale = mShadow->mTransform->GetScale();
		scale.x = mSize;
		mShadow->mTransform->SetScale(scale);
		mShadow->mTransform->SetRotation(mTransform->GetRotation());
		mShadow->SetActive(true);

		mMr->SetActive(true);
		mAnim->PlayAnimation(L"Warning", false);
	}
	void DubwooferBeamBullet::WhileWarning(double time)
	{
		mShadow->mTransform->SetPosition(mTransform->GetPosition());
	}
	void DubwooferBeamBullet::OnActivate()
	{
		mCol->SetActive(true);
		mAnim->PlayAnimation(L"Activate", false);
	}
	void DubwooferBeamBullet::WhileActivate(double time)
	{
	}
	void DubwooferBeamBullet::OnOutro()
	{
		mShadow->SetActive(false);
		mAnim->PlayAnimation(L"Outro", false);
	}
	void DubwooferBeamBullet::WhileOutro(double time)
	{
	}
	void DubwooferBeamBullet::OnDeActivate()
	{
		mCol->SetActive(false);
		mMr->SetActive(false);
		mShadow->SetActive(false);
	}
	void DubwooferBeamBullet::CreateOnBeatAnimation()
	{
		Vector3 baseScale = { 200, (float)application.GetWidth() * 2, 1 };
		
		auto Anim = mShadow->AddComponent<Animator>();
		auto warning = Anim->CreateAnimation(L"Warning");
		warning->AddTintKey(0, { 1, 1, 1, 0.5 });
		warning->AddTintKey(0.3, { 1, 1, 1, 0 });
		warning->AddTintKey(0.6, { 1, 1, 1, 0.5 });
		Anim->PlayAnimation(L"Warning", true);

		Animation* ani = mAnim->CreateAnimation(L"Warning");
		ani->AddTrScaleYKey(0, 0);
		ani->AddTrScaleYKey(2, 200);
		
		ani = mAnim->CreateAnimation(L"Activate");

		float flashDur = 0.05;
		ani->AddColliderActiveKey(0, true);
		ani->AddTrScaleYKey(0, 0);
		ani->AddInterpolationKey(0, 1);
		ani->AddTintKey(0, Color::white);

		ani->AddTrScaleYKey(flashDur, baseScale.y);
		ani->AddTintKey(flashDur, Color::white);
		ani->AddInterpolationKey(flashDur, 1);
		ani->AddInterpolationKey(flashDur, 0);
		ani->AddFunctionKey(flashDur, std::bind(&DubwooferBeamBullet::CameraShake, this));
		
		float disappearDur = 0.1;
		ani = mAnim->CreateAnimation(L"Outro");
		ani->AddTrScaleYKey(0, baseScale.y);
		ani->AddTrScaleYKey(disappearDur, 0);
		ani->AddFunctionKey(disappearDur, std::bind(&Bullet::DeActivate, this));
	}
	void DubwooferBeamBullet::CameraShake()
	{
		Quaternion rot = mTransform->GetRotation();
		if (rot == Quaternion::Identity)
			SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect()->Bump(Vector3::Down);
		if (rot == Quaternion::CreateFromAxisAngle(Vector3::Forward, PI))
			SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect()->Bump(Vector3::Up);
		else if (rot == Quaternion::CreateFromAxisAngle(Vector3::Forward, PI * 0.5))
			SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect()->Bump(Vector3::Left);
		else if (rot == Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI * 0.5))
			SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect()->Bump(Vector3::Right);
	}
}