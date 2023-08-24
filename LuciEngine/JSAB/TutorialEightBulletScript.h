#include "LScript.h"
namespace lu
{
	class Animator;
	class Transform;
}
namespace lu::JSAB
{
#pragma once
	class MoveFoward : public Script
	{
	public:
		MoveFoward(){}
		~MoveFoward(){}

		virtual void Initialize();
		virtual void Update();
		
		void Setup(float startTime, float duration) { mStartTime = startTime, mDuration = duration; }
		void Setup(float startTime, float duration, Vector3 startPos, Vector3 endPos) 
		{
			mStartTime = startTime, mDuration = duration; mStartPos = startPos; mEndPos = endPos;
		}
		void GetEnterAnimator(Animator* anim) { anim = mEnterAnimator; }
	private:
		Animator* mEnterAnimator;
		double mStartTime;
		double mDuration;
		Vector3 mStartPos;
		Vector3 mEndPos;

		Transform* mTr;
	};
}

