#pragma once
#include "LScript.h"
namespace lu
{
	class Animator;
}
namespace lu::JSAB
{
	class TutorialMusicController;
	class TutorialEightBullets;
	class TutorialBurst;
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
		TutorialEightBullets* mStage1Bullets[13];
		TutorialBurst* mBurstBullets[8];
		Animator* mBeatBullets[8];
		int mBurstPoolIdx;
		int mBeatPoolIdx;
	};
}

