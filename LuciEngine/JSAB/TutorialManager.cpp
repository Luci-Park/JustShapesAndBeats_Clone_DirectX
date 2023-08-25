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
		RECT bounds = renderer::mainCamera->GetBoundary();
		for (int i = 0; i < 13; i++)
		{
			mStage1Bullets[i] = object::Instantiate<TutorialEightBulletsPrefab>(eLayerType::Bullet);
			mStage1Bullets[i]->AddComponent<InterpolationMove>();
			mStage1Bullets[i]->SetActive(false);
		}
		{
			mBurstPoolIdx = 0;
			float move = 180;
			Vector3 downStartPos = { 500, (float)bounds.top, 0 };
			Vector3 downEndPos = { 500, (float)bounds.top + move, 0 };
			Vector3 upStartPos = { 500, (float)bounds.bottom, 0 };
			Vector3 upEndPos = { 500, (float)bounds.bottom - move, 0 };
			Vector3 fastStartPos = Vector3::Lerp(downStartPos, downEndPos, 0.455 / 0.875);
			for (int i = 0; i < 5; i++)
			{
				mBurstBullets[i] = object::Instantiate<TutorialBurstBulletsPrefab>(eLayerType::Bullet)->GetComponent<BurstScript>();
				float t = i == 0 ? 0.455 : 0.875;
				mBurstBullets[i]->CreateStraightUpAnimation(upStartPos, upEndPos, 0.455);
				mBurstBullets[i]->CreateStraightDownAnimation(downStartPos, downEndPos, 0.455);
				mBurstBullets[i]->Owner()->SetActive(false);
			}
		}
	}
	void TutorialManager::Update()
	{
		double time = MusicController::_MusicController->GetTime();
		int stage = MusicController::_MusicController->GetStage();
		if (stage == 0)Stage1(time);
		if (stage == 1)Stage2(time);
		if (stage == 2)Stage3(time);
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
			7.691, 8.566, 9.441, 10.316, 11.191, 12.066, 12.941, 13.816
		};
		static int idx = 0;
		if (idx < 8)
		{
			if (beat[idx] <= time)
			{
				mBurstBullets[mBurstPoolIdx]->Owner()->SetActive(true);
				if(idx % 2 == 0) 
					mBurstBullets[mBurstPoolIdx]->PlayStraightDown();
				else 
					mBurstBullets[mBurstPoolIdx]->PlayStraightUp();
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
	void TutorialManager::Stage3(double time)
	{
		{
			const double burstbeat[] = {
				14.619,	15.494,	16.369,	17.244,	18.119,	18.994,	19.869,	20.744
			};
			static int burstIdx = 0;
			if (burstIdx < 8)
			{
				if (burstbeat[burstIdx] <= time)
				{
					mBurstBullets[mBurstPoolIdx]->Owner()->SetActive(true);
					if (burstIdx % 2 == 0)
						mBurstBullets[mBurstPoolIdx]->PlayStraightDown();
					else
						mBurstBullets[mBurstPoolIdx]->PlayStraightUp();
					burstIdx++;
					mBurstPoolIdx++;
					mBurstPoolIdx %= 5;
				}
			}
			else
			{
				if (burstbeat[7] > time)
					burstIdx = 0;
			}
		}
	}
}