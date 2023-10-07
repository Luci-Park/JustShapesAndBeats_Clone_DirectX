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
		void CameraTest(float time);
	private:
		CheckPoint* mCheckPoint;
		TryThisScope* mScope;

		int mbScopeFlag;

	};
}

