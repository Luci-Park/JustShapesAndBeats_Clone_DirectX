#pragma once
#include "Bullet.h"
namespace lu::JSAB
{
	class TutorialBeatBar : public Bullet
	{
	public:
		TutorialBeatBar(){}
		virtual ~TutorialBeatBar(){}

		virtual void Initialize() override;
		void SetRandomPosition();
	private:
		virtual void OnShow() override;
		virtual void OnActivate()override;
		virtual void OnDeActivate()override;
		virtual void WhileShowing() override;
		virtual void WhileActive()override;
		virtual void WhileDeActive()override;

		void CreateOnBeatAnimation();
		void Beat();

	private:
		MeshRenderer* mMr;
		Collider2D* mCol;
		Animator* mAnim;
		const double appearDuration = 1.3;
		const double flashDuration = 0.05;
		const double stayDuration = 0.3;
		const double disappearDuration = 0.05;

		double mTargetTime;
	};
}

