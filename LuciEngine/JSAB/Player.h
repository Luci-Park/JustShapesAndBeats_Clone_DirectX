#pragma once
#include <LScript.h>
namespace lu::JSAB
{
	class lu::Transform;
	class lu::Collider2D;
	class Player : public Script
	{
	public:
		Player();
		virtual ~Player() {};
		virtual void Initialize() override;
		virtual void Update() override;

		void SetDashOutline(GameObject* outline) { mDashOutline = outline; }
		void SetDashEffect(GameObject* effect) { mDashEffect = effect; }
		void ScriptTest();
	private:
		void MoveRotate(Quaternion rotation);
		void MoveScale(Vector3 scale);

		//void DashScale();

		Vector3 GetInputDir();
		Quaternion GetRotation(Vector3 moveDir);
		Vector3 GetMoveScale(Vector3 direction);

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

		GameObject* mDashOutline;
		GameObject* mDashEffect;

	};
}

