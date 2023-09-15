#include "LSceneManager.h"
#include "LCamera.h"
#include "NewTutorialManager.h"
#include "TutorialMusicController.h"
#include "EnemyRoundSpikes.h"
#include "EnemyBurst.h"

namespace lu::JSAB
{
	NewTutorialManager::NewTutorialManager()
		: mSpikes(13)
		, mBursts(10)
	{
	}
	void NewTutorialManager::Initialize()
	{
		mMusic = Owner()->GetComponent<TutorialMusicController>();
		mBounds = SceneManager::MainCamera()->GetBoundary();
		{
			float posY[] = { -51, 41, 230, -230 };
			int indicies[] = { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 2, 3, 2 };
			double beat[] = { 850, 1450, 2100, 2500, 3150, 4200, 4800, 5450, 5850, 6500, 6800, 7150, 7500 };

			for (int i = 0; i < 13; i++)
			{
				auto s = mSpikes.GetNext();
				s->SetPosition({ (float)mBounds.right + 42,posY[indicies[i]], 0 }, { (float)mBounds.left - 42,posY[indicies[i]], 0 });
				s->SetTimeline(mMusic, 0, beat[i], 0);
			}
		}
		{
			double beat[] = { 8200, 8950, 9800, 10600, 11500, 12550,13450,14250, 14950,15150 };
			double warning[] = { 318, 662, 735, 662,735, 834,686,662,675,735 };
			for (int i = 0; i < 10; i++)
			{
				auto b = mBursts.GetNext();
				b->SetTimeline(mMusic, warning[i], beat[i], 0);
				float move = 180;
				if (i % 2 == 0)
				{
					Vector3 startPos = { 500, (float)mBounds.top, 0 };
					Vector3 endPos = { 500, (float)mBounds.top + move, 0 };
					b->SetPosition(startPos, endPos);
				}
				else
				{
					Vector3 startPos = { 500, (float)mBounds.bottom, 0 };
					Vector3 endPos = { 500, (float)mBounds.bottom - move, 0 };
					b->SetPosition(startPos, endPos);
				}
			}
		}
	}
	void NewTutorialManager::Update()
	{
		mBounds = SceneManager::MainCamera()->GetBoundary();
		double time = MusicController::Instance->GetTime();
		int stage = MusicController::Instance->GetStage();

		if (stage == 0)Stage1(time);
		if (stage == 1)Stage2(time);
		if (stage == 2)Stage3(time);
		if (stage == 3)Stage4(time);
		if (stage == 4)Stage5(time);
		if (stage == 5)Stage6(time);
		if (stage == 6)Stage7(time);
		if (stage == 7)Stage8(time);
		if (stage == 8)Stage9(time);
		if (stage == 9)Stage10(time);
		
	}
	void NewTutorialManager::ClearBullets()
	{
	}
	void NewTutorialManager::Stage1(double time)
	{
	}
	void NewTutorialManager::Stage2(double time)
	{
		
		
	}
	void NewTutorialManager::Stage3(double time)
	{
	}
	void NewTutorialManager::Stage4(double time)
	{
	}
	void NewTutorialManager::Stage5(double time)
	{
	}
	void NewTutorialManager::Stage6(double time)
	{
	}
	void NewTutorialManager::Stage7(double time)
	{
	}
	void NewTutorialManager::Stage8(double time)
	{
	}
	void NewTutorialManager::Stage9(double time)
	{
	}
	void NewTutorialManager::Stage10(double time)
	{
	}
}