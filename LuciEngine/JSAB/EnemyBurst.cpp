#include "EnemyBurst.h"
#include "LTime.h"
#include "LCamera.h"
#include "CameraScript.h"
namespace lu::JSAB
{
	void EnemyBurst::BulletSetUp()
	{
		{
			GameObject* fourSide = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
			fourSide->mTransform->SetLocalScale({ 30, 30, 1 });
			fourSide->SetName(L"burstBulletShell");
			mShell = fourSide->mTransform;
			MeshRenderer* mr = fourSide->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(Resources::Load <Material> (L"BurstShellMat", L"quad_circle_bullet"));
			mr->SetColor(Color::white);
			Animator* anim = fourSide->AddComponent<Animator>();
			Animation* ani = anim->CreateAnimation(L"Blink");
			ani->AddInterpolationKey(0, 0);
			ani->AddInterpolationKey(0.07, 1);
			fourSide->AddComponent<Collider2D>()->SetType(eColliderType::Circle);
		}
		{
			float theta = PI * 2 / 8.0f;
			for (int i = 0; i < 8; i++)
			{
				GameObject* burst = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
				MeshRenderer* mr = burst->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(Resources::Load<Material>(L"BurstBulletMat", L"SmallCircle"));
				burst->mTransform->SetScale({ 10, 10, 1 });
				burst->mTransform->SetLocalPosition(Vector3::Zero);
				burst->AddComponent<Collider2D>()->SetType(eColliderType::Circle);

				mBursts[i] = burst->mTransform;
				mParticleDirection[i] = { cosf(theta * i), sinf(theta * i), 0 };
				mParticleDirection[i].Normalize();

				burst->SetActive(false);
			}
		}		
	}
	void EnemyBurst::OnWarning()
	{
		mShell->Owner()->SetActive(true);
		mShell->Owner()->GetComponent<Animator>()->PlayAnimation(L"Blink", true);
	}
	void EnemyBurst::WhileWarning(double time)
	{
		float t = time / mActivateTime;
		Vector3 rot = mShell->GetRotation().ToEuler();
		rot.z += PI * -2 * Time::DeltaTime();
		Vector3 midPos = Vector3::Lerp(mStartPos, mEndPos, 0.8);
		Vector3 midScale = Vector3::Lerp({ 0, 0, 1 }, { 1, 1, 1 }, 0.8);
		Vector3 pos;
		Vector3 size;
		float midTime = 0.8;
		if (t <= midTime)
		{
			pos = Vector3::Lerp(mStartPos, midPos, t / midTime);
			size = Vector3::Lerp({0, 0, 1}, midScale, t / midTime);
		}
		else
		{
			pos = Vector3::Lerp(midPos, mEndPos, t);
			size = Vector3::Lerp(midScale, {1, 1, 1}, t);
		}
		mTransform->SetPosition(pos);
		mTransform->SetScale(size);
	}
	void EnemyBurst::OnActivate()
	{
		mShell->Owner()->SetActive(false);
		mShell->SetLocalRotation(Quaternion::Identity);
		mTransform->SetPosition(mEndPos);
		for (int i = 0; i < 8; i++)
			mBursts[i]->Owner()->SetActive(true);
		mActivatedBullet = 8;
		mCamera->WhiteFlash();
	}
	void EnemyBurst::WhileActivate(double time)
	{
		for (int i = 0; i < 8; i++)
		{
			if (!mBursts[i]->Owner()->IsActive()) return;
			mBursts[i]->SetLocalPosition(mBursts[i]->GetLocalPosition() + mParticleMoveSpeed * Time::DeltaTime() * mParticleDirection[i]);
			Vector3 pos = mBursts[i]->GetPosition() - mBursts[i]->GetScale() * 0.5;
			RECT bounds = SceneManager::MainCamera()->GetBoundary();
			Rectangle bBound = { (long)pos.x,(long)pos.y, (long)mBursts[i]->GetScale().x, (long)mBursts[i]->GetScale().y };
			if (!((Rectangle)bounds).Contains(bBound))
			{
				mBursts[i]->Owner()->SetActive(false);
				mActivatedBullet--;
			}
		}
		if (mActivatedBullet <= 0)
			DeActivate();
	}
	void EnemyBurst::OnDeActivate()
	{
		mShell->Owner()->SetActive(false);
		for (int i = 0; i < 8; i++)
		{
			mBursts[i]->Owner()->SetActive(false);
			mBursts[i]->SetLocalPosition(Vector3::Zero);
		}
	}
}