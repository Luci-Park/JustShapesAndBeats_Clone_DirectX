#include "TutorialManager.h"
#include "TutorialMusicController.h"
#include "TutorialBulletPrefabs.h"
#include "TutorialEightBulletScript.h"
#include "LObject.h"
#include "LRenderer.h"
#include "LAnimator.h"
#include "LApplication.h"

extern lu::Application application;
namespace lu::JSAB
{
	TutorialManager::TutorialManager()
		: mBurstPoolIdx(0)
		, mBeatPoolIdx(0)
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
			float move = 180;
			Vector3 downStartPos = { 500, (float)bounds.top, 0 };
			Vector3 downEndPos = { 500, (float)bounds.top + move, 0 };
			Vector3 upStartPos = { 500, (float)bounds.bottom, 0 };
			Vector3 upEndPos = { 500, (float)bounds.bottom - move, 0 };
			Vector3 fastStartPos = Vector3::Lerp(downStartPos, downEndPos, 0.455 / 0.875);
			for (int i = 0; i < 8; i++)
			{
				mBurstBullets[i] = object::Instantiate<TutorialBurstBulletsPrefab>(eLayerType::Bullet)->GetComponent<BurstScript>();
				mBurstBullets[i]->CreateStraightUpAnimation(upStartPos, upEndPos, 0.455);
				mBurstBullets[i]->CreateStraightDownAnimation(downStartPos, downEndPos, 0.455);
				mBurstBullets[i]->Owner()->SetActive(false);
			}
		}
		for (int i = 0; i < 8; i++)
		{
			mBeatBullets[i] = object::Instantiate<TutorialBeatBulletsPrefab>(eLayerType::Bullet)->GetComponent<Animator>();
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
				mBurstPoolIdx %= 8;
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
			const double beat[] = {
				14.619,	15.494,	16.369,	17.244,	18.119,	18.994,	19.869,	20.744
			};
			static int burstIdx = 0;
			if (burstIdx < 8)
			{
				if (beat[burstIdx] <= time)
				{
					mBurstBullets[mBurstPoolIdx]->Owner()->SetActive(true);
					if (burstIdx % 2 == 0)
						mBurstBullets[mBurstPoolIdx]->PlayStraightDown();
					else
						mBurstBullets[mBurstPoolIdx]->PlayStraightUp();
					burstIdx++;
					mBurstPoolIdx++;
					mBurstPoolIdx %= 8;
				}
			}
			else
			{
				if (beat[7] > time)
					burstIdx = 0;
			}
		}
		{
			const double beat[] =
			{
				14.850, 15.500, 16.583, 17.235, 17.450, 18.313, 18.959, 20.242, 20.697, 21.025
			};
			const float y = application.GetHeight() * 2;
			const float x[] = 
			{
				-120, -23, 14, 51, 88, 125, 162, 199
			};			
			static int idx = 0;

			if (idx < 10)
			{
				if (beat[idx] <= time)
				{
					mBeatBullets[mBeatPoolIdx]->Owner()->mTransform->SetPosition({ x[idx], y, 0});
					mBeatBullets[mBeatPoolIdx]->PlayAnimation(L"OnBeat", false);
					idx++;
					mBurstPoolIdx++;
					mBurstPoolIdx %= 10;
				}
			}
			else
			{
				if (beat[9] > time)
					idx = 0;
			}

		}
	}
}