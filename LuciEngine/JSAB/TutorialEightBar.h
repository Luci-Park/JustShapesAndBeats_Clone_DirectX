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
		virtual void OnShow() {};
		virtual void OnActivate();
		virtual void OnDeActivate();
		virtual void WhileActive() {};
		virtual void WhileDeActive() {}
	private:
		TutorialEightBullets* mBullets[10];
		bool mbMove;
	};
}

