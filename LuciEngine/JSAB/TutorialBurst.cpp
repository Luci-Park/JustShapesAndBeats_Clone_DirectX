#include "TutorialBurst.h"
#include "GeneralEffects.h"
#include "CameraScript.h"
#include "LObject.h"
#include "LAnimator.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "LCollider2D.h"
//#include "TutorialEightBulletScript.h"
#include "LRenderer.h"
#include "LTime.h"

namespace lu::JSAB
{
	void TutorialBurst::Initialize()
	{
		Script::Initialize();

		mBase = Owner()->AddComponent<Animator>();
		bounds = renderer::mainCamera->GetBoundary();
		CreateAnimation();

		{
			GameObject* fourSide = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
			fourSide->mTransform->SetLocalScale({ 30, 30, 1 });
			fourSide->SetName(L"burstBullet");
			MeshRenderer* mr = fourSide->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"quad_circle_bullet"));
			mr->SetColor(Color::white);
			Animator* anim = fourSide->AddComponent<Animator>();
			Animation* ani = anim->CreateAnimation(L"Blink");
			float duration = 0.6;
			float step = 0.07;
			CreateClockwiseAnimation(duration, ani);
			bool current = 0;
			for (float i = 0; i <= duration; i += step)
			{
				ani->AddInterpolationKey(i, current);
				current = !current;
			}
			fourSide->AddComponent<Collider2D>()->SetType(eColliderType::Circle);
			mShell = anim;
		}
		float theta = PI * 2 / 8.0f;
		for (int i = 0; i < 8; i++)
		{
			GameObject* burst = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
			MeshRenderer* mr = burst->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"SmallCircle"));
			burst->mTransform->SetScale({ 10, 10, 1 });
			burst->mTransform->SetLocalPosition(Vector3::Zero);
			burst->AddComponent<Collider2D>()->SetType(eColliderType::Circle);

			mBursts[i] = burst->mTransform;
			mParticleDirection[i] = { cosf(theta * i), sinf(theta * i), 0 };
			mParticleDirection[i].Normalize();

			burst->SetActive(false);
		}

		Bullet::Initialize();
	}

	void TutorialBurst::OnBurst()
	{
		mShell->StopAnimation();
		mShell->Owner()->SetActive(false);
		mbIsBursting = true;
		for (int i = 0; i < 8; i++)
			mBursts[i]->Owner()->SetActive(true);
	}

	void TutorialBurst::OnActivate()
	{
		OnDeActivate();
		mShell->Owner()->SetActive(true);
		mShell->PlayAnimation(L"Blink", true);
		if (mbEven)
		{
			mTransform->SetPosition({ 500, (float)bounds.top, 0 });
			mBase->PlayAnimation(L"Down", false);
		}
		else
		{
			mTransform->SetPosition({ 500, (float)bounds.bottom, 0 });
			mBase->PlayAnimation(L"Up", false);
		}
	}
	
	void TutorialBurst::OnDeActivate()
	{
		mbIsBursting = false;
		mShell->Owner()->SetActive(false);
		for (int i = 0; i < 8; i++)
		{
			mBursts[i]->Owner()->SetActive(false);
			mBursts[i]->SetLocalPosition(Vector3::Zero);
		}
	}

	void TutorialBurst::WhileActive()
	{
		if (!mbIsBursting) return;
		for (int i = 0; i < 8; i++)
		{
			float speed = 300;
			if (mBursts[i]->Owner()->IsActive())
			{
				mBursts[i]->SetLocalPosition(mBursts[i]->GetLocalPosition() + speed * Time::DeltaTime() * mParticleDirection[i]);
				Vector3 pos = mBursts[i]->GetPosition() - mBursts[i]->GetScale() * 0.5;
				Rectangle bBound = { (long)pos.x,(long)pos.y, (long)mBursts[i]->GetScale().x, (long)mBursts[i]->GetScale().y };
				if (!((Rectangle)bounds).Contains(bBound))
					mBursts[i]->Owner()->SetActive(false);
			}
		}
	}
	void TutorialBurst::WhileDeActive()
	{
	}
	
	void TutorialBurst::CreateAnimation()
	{
		float move = 180;
		Vector3 downStartPos = { 500, (float)bounds.top, 0 };
		Vector3 downEndPos = { 500, (float)bounds.top + move, 0 };
		Vector3 upStartPos = { 500, (float)bounds.bottom, 0 };
		Vector3 upEndPos = { 500, (float)bounds.bottom - move, 0 };
		double duration = 0.455;
		Animation* ani = mBase->CreateAnimation(L"Down");
		CreateMoveAnimation(ani, downStartPos, downEndPos, duration);
		ani = mBase->CreateAnimation(L"Up");
		CreateMoveAnimation(ani, upStartPos, upEndPos, duration);
	}

	void TutorialBurst::CreateMoveAnimation(Animation* ani, Vector3 startPos, Vector3 endPos, double duration)
	{
		ani->AddPositionKey(0, startPos);
		Vector3 mid = Vector3::Lerp(startPos, endPos, 0.9);
		ani->AddPositionKey(duration * 0.7, mid);
		ani->AddPositionKey(duration, endPos);

		ani->AddScaleKey(0, Vector3::Zero);
		ani->AddScaleKey(duration, Vector3::One);

		//ani->AddFunctionKey(duration, std::bind(&CameraScript::Flash, renderer::mainCamera->Owner()->GetComponent<CameraScript>()));
		ani->AddFunctionKey(duration, std::bind(&TutorialBurst::OnBurst, this));
	}
}