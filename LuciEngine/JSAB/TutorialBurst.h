#pragma once
#include "Bullet.h"

namespace lu::JSAB
{
	class TutorialBurst : public Bullet
	{
	public:
		TutorialBurst(): mbIsBursting(false){}
		virtual ~TutorialBurst(){}
		virtual void Initialize() override;

		void IsEven(bool even) { mbEven = even; }
		void OnBurst();
	private:
		virtual void OnShow() override {};
		virtual void OnActivate()override;
		virtual void OnDeActivate()override;
		virtual void WhileShowing() override {};
		virtual void WhileActive()override;
		virtual void WhileDeActive()override;

		void CreateAnimation();
		void CreateMoveAnimation(Animation* ani, Vector3 startPos, Vector3 endPos, double duration);

	private:
		Animator* mBase;
		Animator* mShell;
		Transform* mBursts[8];
		Vector3 mParticleDirection[8];

		RECT bounds;
		bool mbIsBursting;
		bool mbEven;
	};
}

