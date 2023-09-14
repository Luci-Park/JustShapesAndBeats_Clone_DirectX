#include "NewTutorialManager.h"
#include "TutorialMusicController.h"
#include "EnemyRoundSpikes.h"
#include "LSceneManager.h"
#include "LCamera.h"
namespace lu::JSAB
{
	void NewTutorialManager::Initialize()
	{
		mMusic = Owner()->GetComponent<TutorialMusicController>();
		RECT bounds = SceneManager::MainCamera()->GetBoundary();
		{
			float posY[] = { -51, 41, 230, -230 };
			int indicies[] = { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 2, 3, 2 };
			double beat[] = { 850, 1450, 2100, 2500, 3150, 4200, 4800, 5450, 5850, 6500, 6800, 7150, 7500 };
			mSpikes = std::vector<EnemyRoundSpikes*>(13);
			for (int i = 0; i < 13; i++)
			{
				mSpikes[i] = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<EnemyRoundSpikes>();
				mSpikes[i]->SetPosition({ (float)bounds.right + 42,posY[indicies[i]], 0}, {(float)bounds.left - 42,posY[indicies[i]], 0});
				mSpikes[i]->SetTimeline(mMusic, 0, beat[i], 0);
			}
		}
	}
	void NewTutorialManager::Update()
	{
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