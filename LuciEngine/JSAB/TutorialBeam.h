#pragma once
#include "Bullet.h"
namespace lu::JSAB
{
	class TutorialBeam : public Bullet
	{
	public:
		TutorialBeam(){}
		virtual ~TutorialBeam(){}
		void SetRandomPosition();
	private:
		virtual void BulletSetUp()override;

		virtual void OnWarning()override;
		virtual void WhileWarning(double time)override;
		virtual void OnActivate()override;
		virtual void WhileActivate(double time)override;
		virtual void OnOutro()override;
		virtual void WhileOutro(double time)override;
		virtual void OnDeActivate()override;

		void CreateOnBeatAnimation();
		void Beat();

	private:
		MeshRenderer* mMr;
		Collider2D* mCol;
		Animator* mAnim;
		const double appearDuration = 1.3;
		const double flashDuration = 0.05;
		const double disappearDuration = 0.1;

		double mTargetTime;
	};
}

