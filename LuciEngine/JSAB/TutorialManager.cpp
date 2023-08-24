#include "TutorialManager.h"
#include "TutorialMusicController.h"
#include "TutorialBulletPrefabs.h"
#include "TutorialEightBulletScript.h"
#include "LObject.h"
#include "LRenderer.h"
namespace lu::JSAB
{
	TutorialManager::TutorialManager()
		:mStage(1)
	{
	}
	void TutorialManager::Initialize()
	{
		for (int i = 0; i < 13; i++)
		{
			mStage1Bullets[i] = object::Instantiate<TutorialEightBulletsPrefab>(eLayerType::Bullet);
			mStage1Bullets[i]->SetActive(false);
			mStage1Bullets[i]->AddComponent<MoveFoward>();
		}
	}
	void TutorialManager::Update()
	{
		double time = MusicController::_MusicController->GetTime();
		if (mStage == 1) Stage1(time);
	}
	void TutorialManager::Stage1(double time)
	{
		const double beat[] = {
			0.763, 1.430, 2.079, 2.497, 3.163, 4.255, 4.886, 5.520, 5.980, 6.638, 6.855, 7.173, 7.471
		};
		const float posY[] = { -51, 41, 230, -230 };//normal, small high, very high, very low
		const int idicies[] = { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 2, 3, 2 };
		static int idx = 0;

		RECT bounds = renderer::mainCamera->GetBoundary();
		float x = bounds.right + mStage1Bullets[0]->mTransform->GetScale().x * 0.5;
		float endX = bounds.left - mStage1Bullets[0]->mTransform->GetScale().x * 0.5;
		idx %= 13;
		if (beat[idx] <= time)
		{
			Vector3 pos = { x, posY[idicies[idx]], 1 };
			Vector3 endPos = {endX, posY[idicies[idx]], 1 };
			mStage1Bullets[idx]->mTransform->SetPosition(pos);
			mStage1Bullets[idx]->GetComponent<MoveFoward>()->Setup(time, 7, pos, endPos);
			mStage1Bullets[idx]->SetActive(true);
			idx++;
		}
	}
}