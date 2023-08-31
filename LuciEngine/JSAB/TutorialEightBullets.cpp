#include "TutorialEightBullets.h"
#include "GeneralEffects.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "LCollider2D.h"
#include "LAnimator.h"
#include "LTime.h"
#include "LObject.h"

namespace lu::JSAB
{
	void TutorialEightBullets::Initialize()
	{
		Script::Initialize();
		Owner()->SetName(L"EightPointBullet");
		mTransform->SetScale(Vector3(42, 42, 1));
		mCol = Owner()->AddComponent<Collider2D>()->SetType(eColliderType::Circle);

		mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"octa_circle_bullet"));

		mAnim = Owner()->AddComponent<Animator>();
		Animation* ani = mAnim->CreateAnimation(L"Rotate");
		CreateClockwiseAnimation(1.f, ani);
		CreateEnterEffect();
		Bullet::Initialize();
	}
	void TutorialEightBullets::Setup(float duration, Vector3 startPos, Vector3 endPos)
	{
		mDuration = duration; 
		mStartPos = startPos; 
		mEndPos = endPos;
		mTime = 0;
		mbIsMoving = mStartPos != mEndPos;
	}
	void TutorialEightBullets::OnActivate()
	{
		mEnterEffect->Owner()->SetActive(true);
		mEnterEffect->PlayAnimation(L"Appear", false);
		mAnim->PlayAnimation(L"Rotate", true);
		mMr->SetActive(true);
		mCol->SetActive(true);

		mTime = 0;
	}
	void TutorialEightBullets::OnDeActivate()
	{
		mEnterEffect->Owner()->SetActive(false);
		mAnim->StopAnimation();
		mMr->SetActive(false);
		mCol->SetActive(false);
	}
	void TutorialEightBullets::WhileActive()
	{
		if (!mbIsMoving) return;
		mTime += Time::DeltaTime();
		float t = mTime / mDuration;
		if (t <= 1.0f)
		{
			Vector3 pos = Vector3::Lerp(mStartPos, mEndPos, t);
			mTransform->SetLocalPosition(pos);
		}
		else
			DeActivate();
	}
	void TutorialEightBullets::WhileDeActive()
	{
	}
	void TutorialEightBullets::CreateEnterEffect()
	{
		GameObject* enterEffect = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
		enterEffect->SetName(L"enterburst");
		enterEffect->mTransform->SetLocalPosition({ 0, 0, -0.1 });

		MeshRenderer* mr = enterEffect->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"circle_bullet_blink_white"));

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