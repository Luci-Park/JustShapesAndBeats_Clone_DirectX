#pragma once
#include "Bullet.h"

namespace lu::JSAB
{
	class TutorialEightBullets;
	class TutorialHalfBar : public Bullet
	{
	public:
		TutorialHalfBar(): mbIsMoving(false){}
		virtual ~TutorialHalfBar(){}

		void Initialize();
		void Setup(float duration, Vector3 startPos, Vector3 endPos);
	private:
		virtual void OnShow() override {};
		virtual void OnActivate()override;
		virtual void OnDeActivate()override;
		virtual void WhileShowing() override {};
		virtual void WhileActive()override;
		virtual void WhileDeActive()override {};
	private:
		TutorialEightBullets* mBullets[10];
		Vector3 mEndPos;
		Vector3 mStartPos;
		double mTime;
		float mDuration;
		bool mbIsMoving;
	};

	class TutorialFullBar : public Bullet
	{
	public:
		TutorialFullBar() : mbIsMoving(false) {}
		virtual ~TutorialFullBar(){}
		void Initialize();
		void Setup(float duration, Vector3 startPos, Vector3 endPos);
	private:
		virtual void OnShow() override {};
		virtual void OnActivate()override;
		virtual void OnDeActivate()override;
		virtual void WhileShowing() override {};
		virtual void WhileActive()override;
		virtual void WhileDeActive()override {};
	private:
		TutorialHalfBar* mHalf[2];
		Vector3 mEndPos;
		Vector3 mStartPos;
		double mTime;
		float mDuration;
		bool mbIsMoving;
	};
}

