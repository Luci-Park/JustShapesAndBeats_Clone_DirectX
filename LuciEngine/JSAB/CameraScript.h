#pragma once
#include "..\Engine_SOURCE\LScript.h"

namespace lu
{
	class Animator;
	class Camera;
}

namespace lu::JSAB
{
	class BackgroundScript;
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
		void LevelTrans();
		void WhiteFadeIn();
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
		virtual void Update() override;

		CameraEffectScript* GetEffect() { return mEffect; }
		BackgroundScript* GetBackground() { return mBackground; }

	private:
		Camera* mGameCamera;
		CameraEffectScript* mEffect;
		BackgroundScript* mBackground;
	};
}

