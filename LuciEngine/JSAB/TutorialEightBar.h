#pragma once
#include "Bullet.h"

namespace lu::JSAB
{
	class TutorialEightBullets;
	class TutorialEightBar : public Bullet
	{
	public:
		TutorialEightBar(): mbMove(false){}
		virtual ~TutorialEightBar(){}

		void Initialize();
		void SetMove(bool move) { mbMove = move; }
	private:
		virtual void OnShow() override {};
		virtual void OnActivate()override;
		virtual void OnDeActivate()override;
		virtual void WhileShowing() override {};
		virtual void WhileActive()override;
		virtual void WhileDeActive()override {};
	private:
		TutorialEightBullets* mBullets[10];
		bool mbMove;
	};
}

