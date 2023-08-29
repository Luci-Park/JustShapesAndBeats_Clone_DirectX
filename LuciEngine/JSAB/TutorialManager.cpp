#include "TutorialManager.h"
#include "TutorialMusicController.h"
#include "TutorialBulletPrefabs.h"
#include "TutorialEightBulletScript.h"
#include "TutorialBeatBar.h"
#include "LObject.h"
#include "LRenderer.h"
#include "LAnimator.h"
#include "LApplication.h"
#include "TutorialEightBullets.h"
#include "TutorialBurst.h"

extern lu::Application application;
namespace lu::JSAB
{
	TutorialManager::TutorialManager()
		: mStage1Bullets(13)
		, mBurstBullets(8)
		, mBeatBars(10)
	{
	}
	void TutorialManager::Initialize()
	{
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
		float x = bounds.right + 42 * 0.5;
		float endX = bounds.left - 42 * 0.5;
	
		if (idx < 13)
		{
			if (beat[idx] <= time)
			{
				Vector3 pos = { x, posY[idicies[idx]], 1 };
				Vector3 endPos = { endX, posY[idicies[idx]], 1 };
				TutorialEightBullets* bullet = mStage1Bullets.GetNext();
				bullet->mTransform->SetPosition(pos);
				bullet->Setup(7, pos, endPos);
				bullet->Activate();
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
				auto bullet = mBurstBullets.GetNext();
				bullet->IsEven(idx % 2 == 0);
				bullet->Activate();
				idx++;
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
			static int idx = 0;
			if (idx < 8)
			{
				if (beat[idx] <= time)
				{
					auto bullet = mBurstBullets.GetNext();
					bullet->IsEven(idx % 2 == 0);
					bullet->Activate();
					idx++;
				}
			}
			else
			{
				if (beat[idx - 1] > time)
					idx = 0;
			}
		}
		{
			const double beat[] =
			{
				14.619, 15.269, 16.352, 17.004, 17.219, 18.082, 18.728, 19.769, 20.466, 20.794
			};
			/*{
				14.850, 15.500, 16.583, 17.235, 17.450, 18.313, 18.959, 20., 20.697, 21.025
			};
			*/
			const float y = application.GetHeight() * 0.5;
			const float x[] = 
			{ 
				-60, - 20, 20, 60, 100, 140, 180, 220, 260, 300
			};
			static int idx = 0;
			if (idx < 8)
			{
				if (beat[idx] <= time)
				{
					auto bullet = mBeatBars.GetNext();
					bullet->mTransform->SetPosition({ x[idx], y, 0 });
					bullet->Activate();
					idx++;
				}
			}
			else
			{
				if (beat[idx - 1] > time)
					idx = 0;
			}

		}
	}
}