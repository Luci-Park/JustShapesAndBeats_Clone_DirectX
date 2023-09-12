#pragma once
#include "LScript.h"
namespace lu
{
	class Animator;
}
namespace lu::JSAB::Title
{
	class SplashAnimation : public Script
	{
	public:
		SplashAnimation(){}
		virtual ~SplashAnimation(){}
		virtual void Initialize() override;

		void FadeIn();
	private:
		Animator* mAnim;
		Animator* mShapes;
		Animator* mAnd;
		Animator* mBeats;
	};
}

