#pragma once
#include "Bullet.h"

namespace lu::JSAB
{
	class TutorialEightBullets : public Bullet
	{
	public:
		TutorialEightBullets() : mTime(0) {}
		virtual ~TutorialEightBullets(){}
		virtual void Initialize() override;
		void Setup(float duration, Vector3 startPos, Vector3 endPos);
	private:
		virtual void OnActivate();
		virtual void OnDeActivate();
		virtual void WhileActive();
		virtual void WhileDeActive();
		
		void CreateEnterEffect();

	private:
		Animator* mAnim;
		Animator* mEnterEffect;
		Collider2D* mCol;
		MeshRenderer* mMr;
		Vector3 mEndPos;
		Vector3 mStartPos;
		double mTime;
		float mDuration;
		bool mbIsMoving;
	};
}

