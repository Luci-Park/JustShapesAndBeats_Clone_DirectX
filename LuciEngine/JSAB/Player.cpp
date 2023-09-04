#include "Player.h"
#include "LInput.h"
#include "LGameObject.h"
#include "LTransform.h"
#include "LTime.h"
#include "LCollider2D.h"
#include "LResources.h"
#include "LMeshRenderer.h"
#include "LTexture.h"
#include "LAnimator.h"
#include "LSceneManager.h"
#include "LCamera.h"
#include "LAudioSource.h"

namespace lu::JSAB
{
	Player::Player()
		: mMoveSpeed(330)
		, mDashSpeed(1320.0f)
		, mDashDuration(.1f)
		, mDashCoolDuration(.2f)
		, mTimer(0.0f)
		, mMoveDir(Vector3::Zero)
		, mMaxHealth(4)
		, mCurrHealth(mMaxHealth)
		, mDashState(eDashState::Idle)
	{
	}
	void Player::Initialize()
	{
		mTr = Owner()->mTransform;
		mCr = Owner()->GetComponent<Collider2D>();
		mMr = Owner()->GetComponent<MeshRenderer>();
		mAnim = Owner()->AddComponent<Animator>();
		mAudio = Owner()->AddComponent<AudioSource>();

		mOrgScale = mTr->GetScale();
		mMoveScale = { mOrgScale.x * 0.7f, mOrgScale.y * 1.3f, 1.f };
		mDashScale = { mOrgScale.x * 0.5f, mOrgScale.y * 2.f, 1.f };
		
		lifeTextures[3] = Resources::Find<graphics::Texture>(L"player1");
		lifeTextures[2] = Resources::Find<graphics::Texture>(L"player22");
		lifeTextures[1] = Resources::Find<graphics::Texture>(L"player41");
		lifeTextures[0] = Resources::Find<graphics::Texture>(L"player61");

		auto a = mAnim->CreateAnimation(L"Flash");
		double duration = 2.0;
		for (int i = 0; i < 40; i++)
		{
			a->AddInterpolationKey(duration / 40 * i, i % 2 ? 0 : 1);
		}

		mHitSounds[0] = Resources::Load<AudioClip>(L"PlayerHit1", L"..\\..\\Assets\\AudioClips\\Player\\SFX_HIT_1.wav");
		mHitSounds[1] = Resources::Load<AudioClip>(L"PlayerHit2", L"..\\..\\Assets\\AudioClips\\Player\\SFX_HIT_2.wav");
	}
	void Player::Update()
	{
		CountTimer();
		Vector3 moveDir = GetInputDir();
	  	if (Input::GetKeyDown(eKeyCode::SPACE) && mDashState == eDashState::Idle)
		{
			mDashState = eDashState::Dashing;
			mTimer = 0.f;
			mDashDir = moveDir == Vector3::Zero ? Vector3::Right : moveDir;
			mDashBurst->mTransform->SetPosition(mTr->GetPosition());
			mDashBurstAnim->PlayAnimation(L"Burst", false);
		}
	
		if (mDashState != eDashState::Dashing)
		{
			mCr->SetState(eState::Active);
			mDashOutline->SetState(eState::InActive);
			Move(mTr->GetPosition() + moveDir * mMoveSpeed * Time::DeltaTime());
			MoveRotate(GetRotation(moveDir));
			MoveScale(GetMoveScale(moveDir));
		}
		else
		{
			if (mTimer > mDashDuration)
			{
				mDashState = eDashState::CoolDown;
				mTimer = 0.0f;
			}
			mCr->SetState(eState::InActive);
			mDashOutline->SetState(eState::Active);

			Move(mTr->GetPosition() + mDashDir * mDashSpeed * Time::DeltaTime());
			MoveRotate(GetRotation(mDashDir));
			mTr->SetScale(mDashScale);
		}
	}
	void Player::OnCollisionEnter(Collider2D* other)
	{
		if (other->Owner()->GetLayer() == eLayerType::Bullet && !mShield->Owner()->IsActive())
			OnDamage();
	}

	void Player::Move(Vector3 target)
	{
		Vector3 halfScale = mTr->GetScale() * 0.5f;
		RECT rect = SceneManager::MainCamera()->GetBoundary();
		Vector3 newPos;
		newPos.z = target.z;
		if (rect.right >= halfScale.x)
		{
			newPos.y = std::clamp(target.y, (float)rect.top + halfScale.y, (float)rect.bottom - halfScale.y);
			newPos.x = std::clamp(target.x, (float)rect.left + halfScale.x, (float)rect.right - halfScale.x);
		}
		mTr->SetPosition(newPos);
	}


	void Player::MoveRotate(Quaternion rotation)
	{
		static Quaternion originalRotation;
		static Quaternion targetRotation = Quaternion::Identity;
		static float timer = 0;
		static float rotateTime = 0.05f;
		if (rotation != targetRotation)
		{
			originalRotation = mTr->GetRotation();
			targetRotation = rotation;
			timer = 0;
			mTr->SetRotation(Quaternion::Identity);
			return;
		}
		if (timer <= rotateTime)
		{
			timer += Time::DeltaTime();
			mTr->SetRotation(Quaternion::Lerp(originalRotation, targetRotation, timer / rotateTime));
		}
		else
		{
			mTr->SetRotation(rotation);
		}
	}
	void Player::MoveScale(Vector3 scale)
	{
		static Vector3 originalScale;
		static Vector3 targetScale = Vector3::One;
		static float timer = 0;
		static float scaleTime = 0.15f;
		if (scale != targetScale)
		{
			originalScale = mTr->GetScale();
			targetScale = scale;
			timer = 0;
			mTr->SetScale(mOrgScale);
			return;
		}
		if (timer <= scaleTime)
		{
			timer += Time::DeltaTime();
			mTr->SetScale(Vector3::Lerp(originalScale, targetScale, timer / scaleTime));
		}
		else
		{
			mTr->SetScale(scale);
		}
	}

	void Player::CountTimer()
	{
		mTimer += Time::DeltaTime();
		if (mDashState == eDashState::CoolDown && mTimer > mDashCoolDuration)
			mDashState = eDashState::Idle;
	}

	Vector3 Player::GetMoveScale(Vector3 direction)
	{
		static Vector3 prevDir = Vector3::Zero;
		if (direction == Vector3::Zero || direction != prevDir)
		{
			prevDir = direction;
			return mOrgScale;
		}
		else
		{
			return mMoveScale;
		}
	}
	void Player::OnDamage()
	{
		PlayHitSound();
		mCurrHealth--;
		if (mCurrHealth > 0)
		{
			mMr->GetMaterial()->SetTexture(lifeTextures[mCurrHealth - 1]);
			mShield->Activate();
			mAnim->PlayAnimation(L"Flash", false);
		}
		else 
			OnDeath();
	}
	void Player::PlayHitSound()
	{
		mAudio->SetClip(mHitSounds[math::IntRandom(0, 1)]);
		mAudio->Play();
	}
	void Player::OnDeath()
	{
	}
	Vector3 Player::GetInputDir()
	{
		Vector3 moveDir = Vector3::Zero;
		if (Input::GetKey(eKeyCode::LEFT))
			moveDir = Vector3::Left;
		if (Input::GetKey(eKeyCode::RIGHT))
			moveDir = Vector3::Right;
		if (Input::GetKey(eKeyCode::UP))
			moveDir = Vector3::Up;
		if (Input::GetKey(eKeyCode::DOWN))
			moveDir = Vector3::Down;
		return moveDir;
	}
	Quaternion Player::GetRotation(Vector3 moveDir)
	{
		float radian = 0;
		if (moveDir == Vector3::Left)
			radian = PI * 0.5f;
		if (moveDir == Vector3::Right)
			radian = -PI * 0.5f;
		if (moveDir == Vector3::Down)
			radian = PI;

		return Quaternion::CreateFromAxisAngle(Vector3::Forward, radian);
	}
	void Player::SetDashBurst(GameObject* burst)
	{
		mDashBurst = burst;
		mDashBurstAnim = mDashBurst->GetComponent<Animator>();
	}
	
#pragma region  ShieldScript
	void ShieldScript::Update()
	{
		mTransform->SetPosition(mPlayer->GetPosition());
	}
	void ShieldScript::CreateAnimation()
	{
		mAnim = Owner()->AddComponent<Animator>();
		auto a = mAnim->CreateAnimation(L"Shield");
		double duration = 1;
		for (int i = 0; i < 85; i++)
		{
			std::wstring name = L"Shield" + std::to_wstring(i + 1);
			a->AddTextureKey(duration / 85.f * i, Resources::Find<Texture>(name));
		}
		a->AddFunctionKey(duration, std::bind(&GameObject::SetActive, Owner(), false));
	}
	void ShieldScript::Activate()
	{
		mAnim->PlayAnimation(L"Shield", false);
		Owner()->SetActive(true);
	}
#pragma endregion

}
