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
	class TutorialBeatCircle; 
	class TutorialFullBar;
	class TutorialCircleLine;
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
		void Stage4(double time);
		void Stage5(double time);
		void Stage6(double time);
		void Stage7(double time);
		void Stage8(double time);
		void Stage9(double time);
		void Stage10(double time);
	private:
		TutorialMusicController* mMusic;
		BulletPool<TutorialEightBullets> mStage1Bullets;
		BulletPool<TutorialBurst> mBurstBullets;
		BulletPool<TutorialBeatBar>mBeatBars;
		BulletPool<TutorialBeatCircle> mBeatCircles;	
		BulletPool<TutorialFullBar> mFullBar;
		BulletPool<TutorialCircleLine> mCircles;
		Animator* mBeatBullets[8];
	};
}

