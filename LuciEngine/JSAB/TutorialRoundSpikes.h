#pragma once
#include "Bullet.h"

namespace lu::JSAB
{
	class TutorialRoundSpikes : public Bullet
	{
	public:
		TutorialRoundSpikes() : mTime(0) {}
		virtual ~TutorialRoundSpikes(){}

		void Setup(float duration, Vector3 startPos, Vector3 endPos);
	private:
		virtual void BulletSetUp()override;
		virtual void OnWarning()override;
		virtual void WhileWarning(double time)override;
		virtual void OnActivate()override;
		virtual void WhileActivate(double time)override;
		virtual void OnOutro()override;
		virtual void WhileOutro(double time)override;
		virtual void OnDeActivate()override;
		
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

