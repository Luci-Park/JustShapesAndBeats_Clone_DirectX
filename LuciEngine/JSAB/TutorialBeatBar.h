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

	private:
		MeshRenderer* mMr;
		Collider2D* mCol;
		Animator* mAnim;
	};
}

