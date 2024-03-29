#pragma once
#include "..\\Engine_SOURCE\\LScript.h"
namespace lu::graphics
{
	class Texture;
}

namespace lu
{
	class Transform;
	class Collider2D;
	class MeshRenderer;
	class Animator;
	class AudioSource;
	class AudioClip;
	class Rigidbody;
}

namespace lu::JSAB
{	
	class ShieldScript;
	class Player : public Script
	{
	public:
		enum class eDashState
		{
			Idle, Dashing, CoolDown
		};
		Player();
		virtual ~Player() {};
		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other);

		void SetDashOutline(GameObject* outline) { mDashOutline = outline; }
		void SetDashBurst(GameObject* burst);
		void SetShield(ShieldScript* shield) { mShield = shield; }

		void Hold();
		void Release();
	private:
		void Move();
		void CheckBoundary();

		void OnDamage(Transform* other);
		void OnDeath();

		void MoveRotate(Quaternion rotation);
		void MoveScale(Vector3 scale);
		void CountDashTimer();
		Vector3 GetInputDir();
		Quaternion GetRotation(Vector3 moveDir);
		Vector3 GetMoveScale(Vector3 velocity);
		
		bool IsShieldUp();

		void PlayHitSound();
		void PlayGetItemSound();
	private:
		float mMoveSpeed;
		float mDashSpeed;
		float mTimer;
		float mDashDuration;
		float mDashCoolDuration;
		eDashState mDashState;

		Vector3 mOrgScale;
		Vector3 mMoveScale;
		Vector3 mDashScale;
		Vector3 mMoveDir;
		Vector3 mDashDir;
		
		Collider2D* mCol;
		MeshRenderer* mMr;
		Animator* mImgAnim;
		AudioSource* mAudio;
		Rigidbody* mRb;

		std::shared_ptr<AudioClip> mHitSounds[2];

		GameObject* mDashOutline;
		GameObject* mDashBurst;

		Animator* mDashBurstAnim;
		ShieldScript* mShield;

		std::shared_ptr<graphics::Texture> lifeTextures[4];
		int mMaxHealth, mCurrHealth;

		bool mbHold;
	};
	class ShieldScript : public Script
	{
	public:
		ShieldScript(){}
		virtual ~ShieldScript(){}

		virtual void Update() override;
		void CreateAnimation();
		void SetBack(GameObject* b) { mBackground = b; }
		void SetPlayer(Transform* b) { mPlayer = b; }
		void Activate();
		bool IsShieldUp() { return Owner()->IsActive(); }
		float ShieldProgress();
	private:
		GameObject* mBackground;
		Transform* mPlayer;
		Animator* mImgAnim;
	};
}

