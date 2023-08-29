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
		
	private:
		virtual void OnActivate();
		virtual void OnDeActivate();
		virtual void WhileActive();
		virtual void WhileDeActive();

		void CreateOnBeatAnimation();

	private:
		MeshRenderer* mMr;
		Collider2D* mCol;
		Animator* mAnim;
		const double appearDuration = 1;
		const double flashDuration = 0.05;
		const double stayDuration = 0.2;
		const double disappearDuration = 0.05;
	};
}

