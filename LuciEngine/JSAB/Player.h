#pragma once
#include <LScript.h>
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
	private:
		void Move(Vector3 target);

		void MoveRotate(Quaternion rotation);
		void MoveScale(Vector3 scale);
		void CountTimer();
		Vector3 GetInputDir();
		Quaternion GetRotation(Vector3 moveDir);
		Vector3 GetMoveScale(Vector3 direction);

		void OnDamage();
		void PlayHitSound();
		void OnDeath();

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
		
		Transform* mTr;
		Collider2D* mCr;
		MeshRenderer* mMr;
		Animator* mAnim;
		AudioSource* mAudio;

		std::shared_ptr<AudioClip> mHitSounds[2];

		GameObject* mDashOutline;
		GameObject* mDashBurst;

		Animator* mDashBurstAnim;
		ShieldScript* mShield;

		std::shared_ptr<graphics::Texture> lifeTextures[4];
		int mMaxHealth, mCurrHealth;
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
	private:
		GameObject* mBackground;
		Transform* mPlayer;
		Animator* mAnim;
	};
}

