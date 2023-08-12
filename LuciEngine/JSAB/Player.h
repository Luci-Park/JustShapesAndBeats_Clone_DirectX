#pragma once
#include <LScript.h>
namespace lu::JSAB
{
	class lu::Transform;
	class Player : public Script
	{
	public:
		Player();
		virtual ~Player() {};
		virtual void Initialize() override;
		virtual void Update() override;
	private:
		void MoveRotate(Quaternion rotation);
		void MoveScale(Vector3 scale);
		//void DashScale();

		Vector3 GetInputDir();
		Quaternion GetRotation(Vector3 moveDir);
		Vector3 GetMoveScale(Vector3 direction);
	private:
		Vector3 mOrgScale;
		Vector3 mMoveScale;
		Vector3 mDashScale;
		float mMoveSpeed;
		float mRotateSpeed;
		Vector3 mMoveDir;
		lu::Transform* mTr;
	};
}

