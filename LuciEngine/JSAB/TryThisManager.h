#pragma once
#include "MusicManager.h"
#include "BulletPool.h"
#include "TryThisScope.h"
#include "TryThisStage.h"
#include "TryThisCrystal.h"
#include "TryThisLaserBullet.h"
#include "TryThisRoundSpike.h"
#include "TryThisScope.h"
#include "TryThisSpotlight.h"
//#include "CameraScript.h"
namespace lu::JSAB
{
	class CheckPoint;
	class TryThisManager : public MusicManager
	{
	public:
		TryThisManager();
		virtual ~TryThisManager() {}

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Play() override;
		virtual void OnMusicEnd() override;

	private:
		void Camera(double time);
		void Light(double time);
		void ActivateStage();
	private:
		CameraEffectScript* mEffect;
		CheckPoint* mCheckPoint;
		TryThisScope* mScope;
		TryThisStage* mStage;
		std::vector<TryThisSpotlight*>mLights;

		int mScopeFlag, mCameraFlag, mLightFlag;
	};
}

