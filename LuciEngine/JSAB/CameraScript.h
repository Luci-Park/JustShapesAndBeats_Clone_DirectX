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
		CameraScript():mbIsBeating(false), mbIsFlashing(false){}
		virtual ~CameraScript(){}
		virtual void Initialize() override;
		virtual void Update() override;
		void OnFlash();
		void OnBeat(Vector3 dir);

	private:
		void Flash();
		void Beat();

	private:
		GameObject* mFlash;
		bool mbIsBeating;
		bool mbIsFlashing;
		Vector3 mDefaultPos;
		Vector3 mBeatDir;
	};
}

