#pragma once
#include "..\Engine_SOURCE\LScript.h"

namespace lu
{
	class Animator;
}

namespace lu::JSAB
{
	class CameraScript : public Script
	{
	public:
		CameraScript() {}
		virtual ~CameraScript(){}
		virtual void Initialize() override;
		void Bump(Vector3 dir);
		void WhiteFlash();
		void BlackFlash();
		void BlackFadeOut();
		void BlackFadeIn();
		void Reset();
	private:

	private:
		Animator* mFlash;
		Animator* mAnim;
	};
}

