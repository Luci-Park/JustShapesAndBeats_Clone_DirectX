#include "TutorialManager.h"
#include "TutorialMusicController.h"
#include "TutorialBulletPrefabs.h"
#include "TutorialEightBulletScript.h"
#include "LObject.h"
#include "LRenderer.h"
namespace lu::JSAB
{
	TutorialManager::TutorialManager()
	{
	}
	void TutorialManager::Initialize()
	{
		for (int i = 0; i < 13; i++)
		{
			mStage1Bullets[i] = object::Instantiate<TutorialEightBulletsPrefab>(eLayerType::Bullet);
			mStage1Bullets[i]->SetActive(false);
			mStage1Bullets[i]->AddComponent<InterpolationMove>();
		}
		for (int i = 0; i < 5; i++)
		{
			mBurstBullets[i] = object::Instantiate<TutorialBurstBulletsPrefab>(eLayerType::Bullet)->GetComponent<BurstScript>();
			mBurstBullets[i]->Owner()->SetActive(false);
		}
	}
	void TutorialManager::Update()
	{
		double time = MusicController::_MusicController->GetTime();
		int stage = MusicController::_MusicController->GetStage();
		if (stage == 0) Stage1(time);
		if (stage == 1) Stage2(time);
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
	
		if (idx < 13)
		{
			if (beat[idx] <= time)
			{
				Vector3 pos = { x, posY[idicies[idx]], 1 };
				Vector3 endPos = { endX, posY[idicies[idx]], 1 };
				mStage1Bullets[idx]->mTransform->SetPosition(pos);
				mStage1Bullets[idx]->GetComponent<InterpolationMove>()->SetDirection(7, pos, endPos);
				mStage1Bullets[idx]->SetActive(true);
				idx++;
			}
		}
		else
		{
			if (beat[12] > time)
				idx = 0;
		}
	}
	void TutorialManager::Stage2(double time)
	{
		const double beat[] = {
			7.691, 8.146, 9.021, 9.896, 10.771, 11.646, 12.521, 13.396//, 14.271
		};
		static int idx = 0;
		static int move = 150;
		RECT bounds = renderer::mainCamera->GetBoundary();
		if (idx < 8)
		{
			if (beat[idx] <= time)
			{
				Vector3 startPos, endPos;
				if (idx % 2)
				{
					startPos = { 500, (float)bounds.bottom, 0 };
					endPos = { 500, (float)bounds.bottom - move, 0 };
				}
				else
				{
					startPos = { 500, (float)bounds.top, 0 };
					endPos = { 500, (float)bounds.top + move, 0 };
				}
				mBurstBullets[mBurstPoolIdx]->Reset();
				mBurstBullets[mBurstPoolIdx]->mStartPos = startPos;
				mBurstBullets[mBurstPoolIdx]->mTargetPos = endPos;
				mBurstBullets[mBurstPoolIdx]->mDuration = 0.875;
				if (idx == 0) mBurstBullets[mBurstPoolIdx]->mTime = beat[1] - time;
				mBurstBullets[mBurstPoolIdx]->Owner()->SetActive(true);
				idx++;
				mBurstPoolIdx++;
				mBurstPoolIdx %= 5;
			}
		}
		else
		{
			if (beat[7] > time)
				idx = 0;
		}
	}
}