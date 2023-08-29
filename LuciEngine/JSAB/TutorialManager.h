#pragma once
#include "LScript.h"
#include "BulletPool.h"
namespace lu
{
	class Animator;
}
namespace lu::JSAB
{
	class TutorialMusicController;
	class TutorialEightBullets;
	class TutorialBurst;
	class TutorialBeatBar;
	class TutorialManager : public Script
	{
	public:
		TutorialManager();

		virtual void Initialize() override;
		virtual void Update() override;

		void SetMusic(TutorialMusicController* music) { mMusic = music; }
	private:
		void Stage1(double time);
		void Stage2(double time);
		void Stage3(double time);
	private:
		TutorialMusicController* mMusic;
		BulletPool<TutorialEightBullets> mStage1Bullets;
		BulletPool<TutorialBurst> mBurstBullets;
		BulletPool<TutorialBeatBar>mBeatBars;
		Animator* mBeatBullets[8];
	};
}

