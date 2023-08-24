#pragma once
#include "LScript.h"
namespace lu::JSAB
{
	class TutorialMusicController;
	class TutorialEightBulletsPrefab;
	class TutorialManager : public Script
	{
	public:
		TutorialManager();

		virtual void Initialize() override;
		virtual void Update() override;

		void SetMusic(TutorialMusicController* music) { mMusic = music; }
	private:
		void Stage1(double time);
	private:
		TutorialMusicController* mMusic;
		int mStage;

		TutorialEightBulletsPrefab* mStage1Bullets[13];

	};
}

