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
	class TutorialRoundSpikes;
	class TutorialBurst;
	class TutorialBeam;
	class TutorialBeatCircle; 
	class TutorialFullBar;
	class TutorialCircleLine;
	class TutorialGiantCircle;
	class TutorialManager : public Script
	{
	public:
		TutorialManager();

		virtual void Initialize() override;
		virtual void Update() override;

		void SetMusic(TutorialMusicController* music) { mMusic = music; }
		void ClearBullets();
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
		BulletPool<TutorialRoundSpikes> mStage1Bullets;
		BulletPool<TutorialBurst> mBurstBullets;
		BulletPool<TutorialBeam>mBeatBars;
		BulletPool<TutorialBeatCircle> mBeatCircles;	
		BulletPool<TutorialFullBar> mFullBar;
		BulletPool<TutorialCircleLine> mCircleLines;
		BulletPool<TutorialGiantCircle> mCircles;
	};
}

