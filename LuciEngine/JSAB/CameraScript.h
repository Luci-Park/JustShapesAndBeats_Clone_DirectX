#pragma once
#include "..\Engine_SOURCE\LScript.h"

namespace lu
{
	class Animator;
}

namespace lu::JSAB
{
	class CameraEffectScript : public Script
	{
	public:
		CameraEffectScript() {}
		virtual ~CameraEffectScript(){}
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

	class GameCamera : public Script
	{
	public:
		GameCamera(){};
		virtual ~GameCamera(){}
		virtual void Initialize() override;

		CameraEffectScript* GetEffect() { return mEffect; }
		

	private:
		CameraEffectScript* mEffect;
	};
}

