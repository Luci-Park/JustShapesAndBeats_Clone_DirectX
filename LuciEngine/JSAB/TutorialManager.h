#pragma once
#include "LScript.h"
#include "BulletPool.h"
namespace lu::JSAB
{
	class BackgroundScript;
	class TutorialMusicController;
	class TutorialRoundSpikes;
	class TutorialBurst;
	class TutorialBeam;
	class TutorialBeatCircle; 
	class TutorialGiantCircle;
	class TutorialCircleLine;
	class Triangle;
	class TutorialManager : public Script
	{
	public:
		TutorialManager();
		virtual void Initialize() override;
		virtual void Update() override;
		void OnStageChange(int stage);
		void SetMusic(TutorialMusicController* music) { mMusic = music; }
	private:
		void Stage1();
		void Stage2();
		void Stage3();
		void Stage4();
		void Stage5();
		void Stage6();
		void Stage7();
		void Stage8();
		void Stage9();
		void Stage10();
	private:
		TutorialMusicController* mMusic;
		Triangle* mLevelTriangle;

		BulletPool<TutorialRoundSpikes> mRoundSpikes;
		BulletPool<TutorialBurst> mBursts;
		BulletPool<TutorialBeam>mBeams;
		BulletPool<TutorialCircleLine> mCircleLines;
		BulletPool<TutorialBeatCircle> mBeatCircles;
		BulletPool<TutorialGiantCircle> mGCircles;

		BackgroundScript* mBackground;
	};
}

