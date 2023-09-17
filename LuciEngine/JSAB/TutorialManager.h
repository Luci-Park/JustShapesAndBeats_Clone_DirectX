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
	class TutorialGiantCircle;
	class TutorialManager : public Script
	{
	public:
		TutorialManager();
		virtual void Initialize() override;
		void OnStageChange(int stage);
		void SetMusic(TutorialMusicController* music) { mMusic = music; }
	private:
		void Stage1();
		void Stage2();
		void Stage3();
		/*
		void Stage4();
		void Stage5();
		void Stage6();
		void Stage7();
		void Stage8();
		void Stage9();
		void Stage10();*/
	private:
		TutorialMusicController* mMusic;
		BulletPool<TutorialRoundSpikes> mRoundSpikes;
		BulletPool<TutorialBurst> mBursts;
		BulletPool<TutorialBeam>mBeams;
		BulletPool<TutorialBeatCircle> mBeatCircles;
		BulletPool<TutorialGiantCircle> mGCircles;
	};
}

