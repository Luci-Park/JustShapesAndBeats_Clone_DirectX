#pragma once
#include "LScript.h"

namespace lu
{
	class Animator;
}

namespace lu::JSAB
{
	class CameraScript : public Script
	{
	public:
		CameraScript(){}
		virtual ~CameraScript(){}
		void Initialize();
		void Flash();
		void BeatUp();
		void BeatDown();
		void BeatLeft();
		void BeatRight();

	private:
		void CreateAnimation();
		void SetFlash(bool active) { mFlash->SetActive(active); }
	private:
		GameObject* mFlash;
		Animator* mAnim;
	};
}

