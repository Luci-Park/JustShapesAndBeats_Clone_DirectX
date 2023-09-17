#pragma once
#include "Bullet.h"

namespace lu::JSAB
{
	class TutorialBurst : public Bullet
	{
	public:
		TutorialBurst(){}
		virtual ~TutorialBurst(){}

		void SetUp(Vector3 start, Vector3 end);
	private:
		virtual void BulletSetUp()override;

		virtual void OnWarning()override;
		virtual void WhileWarning(double time)override;
		virtual void OnActivate()override;
		virtual void WhileActivate(double time)override;
		virtual void OnOutro()override;
		virtual void WhileOutro(double time)override;
		virtual void OnDeActivate()override;

		void CreateAnimation();
		void CreateMoveAnimation(Animation* ani, Vector3 startPos, Vector3 endPos, double duration);

	private:
		Animator* mBase;
		Animator* mShell;
		Transform* mBursts[8];
		Vector3 mParticleDirection[8];

		Vector3 mStartPos, mEndPos;
	};
}

