#include "TutorialBurst.h"
#include "GeneralEffects.h"
#include "LSceneManager.h"
#include "LCamera.h"
#include "LTime.h"

namespace lu::JSAB
{
	void TutorialBurst::SetUp(Vector3 start, Vector3 end)
	{
		mStartPos = start;
		mEndPos = end;
	}
	void TutorialBurst::BulletSetUp()
	{
		mBase = Owner()->AddComponent<Animator>();
		CreateAnimation();

		{
			GameObject* fourSide = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
			fourSide->mTransform->SetLocalScale({ 42, 42, 1 });
			fourSide->SetName(L"burstBullet");
			MeshRenderer* mr = fourSide->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(Resources::Load<Material>(L"ShellMat", L"quad_circle_bullet"));
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
	}

	void TutorialBurst::OnWarning()
	{
		mShell->Owner()->SetActive(true);
		mShell->PlayAnimation(L"Blink", true);
		mTransform->SetPosition(mStartPos);
		/*
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
		*/
	}

	void TutorialBurst::WhileWarning(double time)
	{
		float t = 1 - (mActivateTime - time) / mWarningTime;
		Vector3 midPoint = Vector3::Lerp(mStartPos, mEndPos, 0.8);
		Vector3 midScale = Vector3::Lerp({ 0, 0, 1 }, { 1, 1, 1 }, 0.8);
		Vector3 pos = mStartPos;
		Vector3 scale = { 0, 0, 1 };
		if (t <= .5)
		{
			pos = Vector3::Lerp(mStartPos, midPoint, t * 2);
			scale = Vector3::Lerp({ 0, 0, 1 }, midScale, t * 2);
		}
		else
		{
			pos = Vector3::Lerp(midPoint, mEndPos, (t - 0.5) * 2);
			scale = Vector3::Lerp(midScale, { 1, 1, 1 }, (t - 0.5) * 2);
		}
		mTransform->SetPosition(pos);
		mTransform->SetScale(scale);
	}

	void TutorialBurst::OnActivate()
	{
		mShell->StopAnimation();
		mShell->Owner()->SetActive(false);
		for (int i = 0; i < 8; i++)
			mBursts[i]->Owner()->SetActive(true);
		mCamera->WhiteFlash();
	}

	void TutorialBurst::WhileActivate(double time)
	{
		int activs = 0;
		for (int i = 0; i < 8; i++)
		{
			float speed = 300;
			if (mBursts[i]->Owner()->IsActive())
			{
				mBursts[i]->SetLocalPosition(mBursts[i]->GetLocalPosition() + speed * Time::DeltaTime() * mParticleDirection[i]);
				Vector3 pos = mBursts[i]->GetPosition() - mBursts[i]->GetScale() * 0.5;
				Rectangle bBound = { (long)pos.x,(long)pos.y, (long)mBursts[i]->GetScale().x, (long)mBursts[i]->GetScale().y };
				if (!((Rectangle)mBounds).Contains(bBound))
					mBursts[i]->Owner()->SetActive(false);
			}
			else
			{
				activs++;
			}
		}
		if (activs >= 8)DeActivate();
	}

	void TutorialBurst::OnOutro()
	{
	}

	void TutorialBurst::WhileOutro(double time)
	{
	}
	
	void TutorialBurst::OnDeActivate()
	{
		mShell->Owner()->SetActive(false);
		for (int i = 0; i < 8; i++)
		{
			mBursts[i]->Owner()->SetActive(false);
			mBursts[i]->SetLocalPosition(Vector3::Zero);
		}
	}

	void TutorialBurst::CreateAnimation()
	{/*
		float move = 180;
		Vector3 downStartPos = { 500, (float)bounds.top, 0 };
		Vector3 downEndPos = { 500, (float)bounds.top + move, 0 };
		Vector3 upStartPos = { 500, (float)bounds.bottom, 0 };
		Vector3 upEndPos = { 500, (float)bounds.bottom - move, 0 };
		double duration = 0.755;
		Animation* ani = mBase->CreateAnimation(L"Down");
		CreateMoveAnimation(ani, downStartPos, downEndPos, duration);
		ani = mBase->CreateAnimation(L"Up");
		CreateMoveAnimation(ani, upStartPos, upEndPos, duration);*/
	}

	void TutorialBurst::CreateMoveAnimation(Animation* ani, Vector3 startPos, Vector3 endPos, double duration)
	{
		ani->AddPositionKey(0, startPos);
		Vector3 mid = Vector3::Lerp(startPos, endPos, 0.9);
		ani->AddPositionKey(duration * 0.7, mid);
		ani->AddPositionKey(duration, endPos);

		ani->AddScaleKey(0, Vector3::Zero);
		ani->AddScaleKey(duration, Vector3::One);
	}
}