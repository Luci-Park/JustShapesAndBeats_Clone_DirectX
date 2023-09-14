#pragma once
#include "LScript.h"
namespace lu::JSAB
{
	class TutorialMusicController;
	class EnemyRoundSpikes;
	class NewTutorialManager : public Script
	{
	public:
		NewTutorialManager() {};

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
		std::vector<EnemyRoundSpikes*> mSpikes;
	};
}

