#pragma once
#include "LScript.h"
namespace lu
{
	class Animator;
	class Animation;
	class Transform;
}
namespace lu::JSAB
{
	class InterpolationMove : public Script
	{
	public:
		InterpolationMove(){}
		~InterpolationMove(){}

		virtual void Initialize();
		virtual void Update();
		
		void SetDirection(float duration, Vector3 startPos, Vector3 endPos) 
		{
			mDuration = duration; mStartPos = startPos; mEndPos = endPos;
			mTime = 0;
		}
		void GetEnterAnimator(Animator* anim) { anim = mEnterAnimator; }
	private:
		Animator* mEnterAnimator;
		Transform* mTr;
		Vector3 mStartPos;
		Vector3 mEndPos;
		double mDuration;
		double mTime;

	};
	class BurstParticleScript : public Script
	{
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		void Reset();
		void SetDirection(Vector3 direction) { mDirection = direction; Reset(); }
	private:
		Transform* mTr;
		Vector3 mDirection;
		float mSpeed;
		bool mMove;
	};

	class BurstScript : public Script
	{
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void OnEnable() override;
		void Reset();
		void EnableBurst();
		void DisableBurst();
		void CreateStraightDownAnimation(Vector3 startPos, Vector3 endPos, double duration);
		void CreateStraightUpAnimation(Vector3 startPos, Vector3 endPos, double duration);
		void CreateStraightFastAnimation(Vector3 startPos, Vector3 endPos, double duration);
		void CreateStraightAnimation(Animation* ani, Vector3 startPos, Vector3 endPos, double duration);
		void PlayStraightUp();
		void PlayStraightDown();
		void PlayStraightFast();
		
		GameObject* mQuadCircle;
		BurstParticleScript* mBursts[8];
	private:
		Transform* mTr;
		Animator* mAnim;
		Vector3 mTargetPos;
		Vector3 mStartPos;
		double mDuration;
		double mTime;
	};
}

