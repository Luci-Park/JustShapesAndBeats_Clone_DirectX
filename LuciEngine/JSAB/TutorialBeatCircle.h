#pragma once
#include "Bullet.h"
namespace lu::JSAB
{
	class TutorialBeatCircle : public Bullet
	{
	public:
		TutorialBeatCircle(){}
		virtual ~TutorialBeatCircle(){}
		virtual void Initialize()override;
		void SetTime(double targetTime, double currentTime);
	private:
		virtual void OnActivate();
		virtual void OnDeActivate();
		virtual void WhileActive();
		virtual void WhileDeActive();

		void CreateOnBeatAnimation();

	};
}

