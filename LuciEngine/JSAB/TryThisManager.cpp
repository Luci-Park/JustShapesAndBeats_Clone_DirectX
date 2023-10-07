#include "LCamera.h"
#include "TryThisManager.h"
#include "CameraScript.h"
#include "CheckPoint.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"

namespace lu::JSAB
{
	TryThisManager::TryThisManager()
	{
	}
	void TryThisManager::Initialize()
	{
		mNextScene = L"TitleScene";
		mMusic = Owner()->GetComponent<MusicController>();
		mCheckPoint = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<CheckPoint>();
		mCheckPoint->SetBackground(SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetBackground());
		mCheckPoint->SetManager(this);

		//mScope = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisScope>();
		//mScope->SetTimeline(mMusic, 0, .850, 8.400 - .850);

		auto stage = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<TryThisStage>();
		stage->Activate();
		{
			auto light = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisSpotlight>();
			light->Warning();
			light->SetCenter({ -264.864, 0, 0 });
			light->RotateClockWise();
			light->SetStartAngle(210);

			light = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisSpotlight>();
			light->Warning();
			light->SetCenter({ 264.864, 0, 0 });
			light->RotateCounterClockWise();
			light->SetStartAngle(-30);

			light = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisSpotlight>();
			light->Warning();
			light->SetCenter({ 1190.2592, -9.408161, 0 });
			light->RotateClockWise();
			light->SetStartAngle(210);

			light = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisSpotlight>();
			light->Warning();
			light->SetCenter({ 1931.6791, -14.669791, 0 });
			light->RotateCounterClockWise();
			light->SetStartAngle(90);

			light = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisSpotlight>();
			light->Warning();
			light->SetCenter({ 2621.489, 140.8391, 0 });
			light->RotateCounterClockWise();
			light->SetStartAngle(290);

			light = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisSpotlight>();
			light->Warning();
			light->SetCenter({ 3122.3633, 74.33054, 0 });
			light->RotateClockWise();
			light->SetStartAngle(-100);

			light = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisSpotlight>();
			light->Warning();
			light->SetCenter({ 3837.9368, 80.56461, 0 });
			light->RotateClockWise();
			light->SetStartAngle(15);
		}
		{
			auto light = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisSpotlight>();
			light->Warning();
			light->SetCenter({ 3837.9368, 80.56461, 0 });
			light->RotateClockWise();
			light->SetStartAngle(15);
		}
		{
			auto laser = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<TryThisLaserBullet>();
			laser->mTransform->SetPosition(921.45526, 0, 0);
			laser->Activate();
			laser->RotateClockWise();

			laser = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<TryThisLaserBullet>();
			laser->mTransform->SetPosition(5234.5376 + 300, 50, 0);
			laser->Activate();
			laser->RotateClockWise();

			laser = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<TryThisLaserBullet>();
			laser->mTransform->SetPosition(5234.5376 - 300, 50, 0);
			laser->Activate();
			laser->RotateClockWise();

			laser = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<TryThisLaserBullet>();
			laser->mTransform->SetPosition(5234.5376-300, -250, 0);
			laser->Activate();
			laser->RotateClockWise();

			laser = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<TryThisLaserBullet>();
			laser->mTransform->SetPosition(5234.5376 + 300, -250, 0);
			laser->Activate();
			laser->RotateClockWise();

			laser = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<TryThisLaserBullet>();
			laser->mTransform->SetPosition(5234.5376 - 300, 250, 0);
			laser->Activate();
			laser->RotateClockWise();

			laser = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<TryThisLaserBullet>();
			laser->mTransform->SetPosition(5234.5376 + 300, 250, 0);
			laser->Activate();
			laser->RotateClockWise();
		}
	}
	void TryThisManager::Update()
	{
		double time = mMusic->GetTime();
		CameraTest(time);
		MusicManager::Update();
	}
	void TryThisManager::Play()
	{
		mbScopeFlag = 0;
		MusicManager::Play();
	}
	void TryThisManager::OnMusicEnd()
	{
		mMusic->Finish();
		mbFin = true;
	}
	void TryThisManager::CameraTest(float time)
	{
		static float beat[] = { 0.85
, 2.95
, 3.425
, 3.9
, 5.55
, 6.075
, 6.6
, 8.4
, 8.572
, 8.744
, 8.916
, 9.088
, 9.259
, 9.431
, 9.603
, 9.775
, 9.947
, 10.119
, 10.291
, 10.463
, 10.634
, 10.806
, 10.978
, 11.15
, 11.2
, 11.3
, 13.450
, 13.600
, 13.750
, 13.900
, 16.250
, 16.600
, 18.900
, 19.050
, 19.200
, 19.350
, 22.150
, 22.150
, 22.200
, 22.850
, 24.100
, 23.500
, 24.500
, 24.650
, 24.800
, 24.900
, 24.950
, 25.600
, 26.300
, 26.950
, 27.350
, 27.650
, 27.700
, 28.400
, 29.050
, 29.700
, 29.850
, 30.000
, 30.150
, 30.300
, 30.400
, 30.450
, 31.050
, 31.750
, 32.450
, 33.100
, 33.100
, 33.200
, 35.5
, 35.65
, 33.85
, 34.55
, 35.25
, 35.8
, 35.95
, 35.95
, 38.5
, 36.65
, 37.4
, 38.05
, 38.8
, 38.8
, 40.95
, 41.133
, 39.45
, 40.15
, 40.75
, 41.317
, 41.45
, 41.5
, 42.15
, 44.3
, 42.8
, 43.5
, 44.15
, 44.6
, 47.1
, 47.4
, 49.9
, 50.2
, 52.65
, 52.95
, 54.1
, 54.4
, 55.6
, 56.15
, 63.95
, 64.05
, 64.1
, 64.1
, 64.15
, 64.15
, 66.05
, 66.5
, 68.5
, 66.55
, 68.65
, 66.7
, 68.85
, 69.05
, 67.4
, 67.8
, 67.9
, 68.2
, 68.4
, 68.4
, 69.05
, 71.55
, 69.7
, 69.7
, 71.85
, 69.9
, 70.05
, 70.2
, 70.3
, 70.4
, 70.7
, 71
, 71.1
, 71.2
, 74.15
, 74.3
, 74.5
, 72.55
, 74.6
, 74.6
, 74.7
, 72.7
, 72.75
, 72.9
, 73.2
, 73.3
, 73.65
, 73.8
, 73.9
, 73.95
, 74.1
, 74.25
, 74.45
, 74.55
, 75.25
, 77.45
, 75.9
, 76.55
, 77.3
, 79.45
, 79.6
, 79.8
, 78
, 78
, 80
, 78.25
, 78.4
, 78.65
, 78.7
, 79.1
, 79.3
, 79.35
, 79.45
, 80.15
, 82.5
, 80.7
, 80.8
, 82.8
, 80.85
, 81.05
, 81.2
, 81.35
, 81.5
, 81.75
, 82
, 82.1
, 82.2
, 82.9
, 85.1
, 85.25
, 85.45
, 83.55
, 83.6
, 85.65
, 83.8
, 83.9
, 85.95
, 84.25
, 84.35
, 84.65
, 84.8
, 86.85
, 84.9
, 85
, 85.1
, 85.35
, 85.6
, 86.25
, 88.55
, 86.95
, 87.7
, 88.3
, 88.55
, 89.05
, 91.15
, 89.35
, 89.7
, 89.8
, 91.8
, 90.25
, 90.45
, 92.55
, 90.55
, 91.1
, 93.25
, 91.8
, 93.9
, 92.45
, 93.15
, 93.8
, 93.85
, 94.3
, 94.55
, 96.75
, 94.8
, 94.9
, 95.1
, 95.2
, 95.3
, 97.4
, 96
, 96
, 98.15
, 96.65
, 98.85
, 97.3
, 99.5
, 98
, 98.7
, 99.35
, 99.45
, 100.05
, 102.05
, 100.1
, 102.7
, 100.75
, 100.8
, 101.15
, 101.35
, 103.45
, 101.45
, 101.5
, 101.9
, 102.1
, 104.15
, 102.8
, 104.85
, 103.4
, 104.2
, 104.9
, 105.55
, 105.85
, 106
, 106.15
, 106.25
, 106.3
, 107
, 107
, 107.5
, 107.55
, 107.65
, 109.3
, 116.009
		};
		static int idx = 0;
		if (idx < 289 && time >= beat[idx])
		{
			SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect()->Bump(Vector3::Up);
			DEBUGLOG((std::to_string(beat[idx]) + "\n").c_str());
			idx++;
		}

	}
}