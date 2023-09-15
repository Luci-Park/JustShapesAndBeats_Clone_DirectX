#pragma once
#include "LScript.h"
#include "EnemyContainer.h"

namespace lu::JSAB
{
	class EnemyRoundSpikes;
	class EnemyBurst;
	class TutorialMusicController;
	class NewTutorialManager : public Script
	{
	public:
		NewTutorialManager();

		virtual void Initialize() override;
		virtual void Update() override;
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
		EnemyContainer<EnemyRoundSpikes> mSpikes;
		EnemyContainer<EnemyBurst> mBursts;

		RECT mBounds;
	};
}

