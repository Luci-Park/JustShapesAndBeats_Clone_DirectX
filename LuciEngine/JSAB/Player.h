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
}

namespace lu::JSAB
{	
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

		void SetDashOutline(GameObject* outline) { mDashOutline = outline; }
		void SetDashBurst(GameObject* burst);
	private:
		void Move(Vector3 target);

		void MoveRotate(Quaternion rotation);
		void MoveScale(Vector3 scale);
		void CountTimer();
		Vector3 GetInputDir();
		Quaternion GetRotation(Vector3 moveDir);
		Vector3 GetMoveScale(Vector3 direction);

		void OnDamage();

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

		GameObject* mDashOutline;
		GameObject* mDashBurst;

		Animator* mDashBurstAnim;

		std::shared_ptr<graphics::Texture> lifeTextures[4];
		int mMaxHealth, mCurrHealth;
	};
	
}

