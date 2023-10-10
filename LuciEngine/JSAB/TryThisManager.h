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
		void CameraMove(double time);
		void CameraBump(double time);
		void Light(double time);
		void Laser(double time);
		void RoundSpikes(double time);
		void Stage(double time);
		void CheckPoints(double time);
		void ActivateStage();
	private:
		CheckPoint* mCheckPoint;
		CameraEffectScript* mEffect;
		TryThisScope* mScope;
		TryThisStage* mStage;
		std::vector<TryThisSpotlight*>mLights;
		std::vector<TryThisSpotlight*>mStage2Lights;
		BulletPool<TryThisLaserBullet> mLasers;
		BulletPool<TryThisRoundSpike> mSpikes;

		int mLaserFlag, mCameraFlag, mLightFlag, mStageFlag, mSpikeFlag, mCheckPointFlag;
	};
}

