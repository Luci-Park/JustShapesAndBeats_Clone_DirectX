#pragma once
#include <LScript.h>
namespace lu::graphics
{
	class Texture;
}
namespace lu::JSAB
{
	class lu::Transform;
	class lu::Collider2D;
	class lu::MeshRenderer;
	class Player : public Script
	{
	public:
		Player();
		virtual ~Player() {};
		virtual void Initialize() override;
		virtual void Update() override;

		void SetDashOutline(GameObject* outline) { mDashOutline = outline; }
		void SetDashEffect(GameObject* effect) { mDashEffect = effect; }
	private:
		void MoveRotate(Quaternion rotation);
		void MoveScale(Vector3 scale);

		//void DashScale();

		Vector3 GetInputDir();
		Quaternion GetRotation(Vector3 moveDir);
		Vector3 GetMoveScale(Vector3 direction);

		void OnDamage();

	private:
		float mMoveSpeed;
		float mDashSpeed;
		float mDashTimer;
		float mDashDuration;

		bool mIsDashing;
		
		Vector3 mOrgScale;
		Vector3 mMoveScale;
		Vector3 mDashScale;
		Vector3 mMoveDir;
		Vector3 mDashDir;
		
		lu::Transform* mTr;
		lu::Collider2D* mCr;
		lu::MeshRenderer* mMr;

		GameObject* mDashOutline;
		GameObject* mDashEffect;

		std::shared_ptr<graphics::Texture> lifeTextures[4];
		int mMaxHealth, mCurrHealth;
	};
	class lu::MeshRenderer;
	class AnimationTester : public Script
	{
	public:
		AnimationTester(){}
		~AnimationTester(){}

		void Initialize();
		Transform* mTr;
		Collider2D* mCd;
		lu::MeshRenderer* mMr;
	};
}

