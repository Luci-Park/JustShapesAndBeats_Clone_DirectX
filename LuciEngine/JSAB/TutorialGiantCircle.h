#pragma once
#include "Bullet.h"

namespace lu::JSAB
{
	class TutorialGiantCircle : public Bullet
	{
	public:
		TutorialGiantCircle();
		~TutorialGiantCircle();

		virtual void Initialize() override;

		void ActivateWithTime(double time);
	protected:
		virtual void OnShow();
		virtual void OnActivate() {};
		virtual void OnDeActivate();
		virtual void WhileShowing();
		virtual void WhileActive();
		virtual void WhileDeActive() {};

		void CreateAnimation();
	private:
		Animator* mImgAnim;
		MeshRenderer* mMr;
		double mTime;
	};
}

