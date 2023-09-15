#pragma once
#include "Enemy.h"

namespace lu::JSAB
{
	class EnemyRoundSpikes : public Enemy
	{
	public:
		EnemyRoundSpikes(){}
		virtual ~EnemyRoundSpikes(){}
		void SetPosition(Vector3 mStart, Vector3 mEnd);
	protected:
		virtual void BulletSetUp() override;
		virtual void OnWarning()override {}
		virtual void WhileWarning(double time)override {}
		virtual void OnActivate()override;
		virtual void WhileActivate(double time)override;
		virtual void OnOutro()override {}
		virtual void WhileOutro(double time)override {}
		virtual void OnDeActivate() override;
	private:
		MeshRenderer* mMr;
		Animator* mEnterEffect;
		float mRotateSpeed;
		float mMoveSpeed;
		float mMoveTime;
		Vector3 mStartPos;
		Vector3 mEndPos;
	};
}

