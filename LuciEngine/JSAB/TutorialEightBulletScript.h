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
		
		void Setup(float duration, Vector3 startPos, Vector3 endPos) 
		{
			mDuration = duration; mStartPos = startPos; mEndPos = endPos;
			mTime = 0;
		}
		void GetEnterAnimator(Animator* anim) { anim = mEnterAnimator; }
	private:
		Animator* mEnterAnimator;
		double mTime;
		double mDuration;
		Vector3 mStartPos;
		Vector3 mEndPos;

		Transform* mTr;
	};
}

