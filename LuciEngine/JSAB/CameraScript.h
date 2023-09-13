#pragma once
#include "LScript.h"

namespace lu
{
	class MeshRenderer;
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
		void OnWhiteFlash();
		void OnBlackFadeOut();
		void OnBeat(Vector3 dir);
		void TurnEffectOff();

	private:
		void Flash();
		void Beat();
		void FadeIn();
		void FadeOut();

	private:
		MeshRenderer* mFlash;
		bool mbIsBeating;
		bool mbIsFlashing;
		bool mbIsFadingIn;
		bool mbIsFadingOut;
		Vector3 mDefaultPos;
		Vector3 mBeatDir;
	};
}

