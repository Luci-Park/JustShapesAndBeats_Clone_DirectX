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
		Player();
		virtual ~Player() {};
		virtual void Initialize() override;
		virtual void Update() override;

		void SetDashOutline(GameObject* outline) { mDashOutline = outline; }
		void SetDashBurst(GameObject* burst);
	private:
		void MoveRotate(Quaternion rotation);
		void MoveScale(Vector3 scale);

		Vector3 GetInputDir();
		Quaternion GetRotation(Vector3 moveDir);
		Vector3 GetMoveScale(Vector3 direction);

		void OnDamage();

	private:
		float mMoveSpeed;
		float mDashSpeed;
		float mDashTimer;
		float mDashDuration;
		float mDashCoolTime;
		bool mbDashing;
		
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
	/*
	class AnimationTester : public Script
	{
	public:
		AnimationTester(){}
		~AnimationTester(){}

		void Initialize();
		Transform* mTr;
		Collider2D* mCd;
		lu::MeshRenderer* mMr;
	};*/
}

