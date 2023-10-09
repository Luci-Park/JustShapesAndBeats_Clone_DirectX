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
		mEffect = SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetEffect();

		SceneManager::MainCamera()->Owner()->AddComponent<gui::TransformWidget>();

		mCheckPoint = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<CheckPoint>();
		mCheckPoint->SetBackground(SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetBackground());
		mCheckPoint->SetManager(this);

		mScope = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisScope>();
		mScope->SetTimeline(mMusic, 0, .850, 11.3 - .850);

		mStage = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<TryThisStage>();
		mStage->Activate();
		{
			auto light = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisSpotlight>();
			light->SetCenter({ -264.864, 0, 0 });
			light->RotateClockWise();
			light->SetStartAngle(210);
			mLights.push_back(light);

			light = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisSpotlight>();
			light->SetCenter({ 264.864, 0, 0 });
			light->RotateCounterClockWise();
			light->SetStartAngle(-30);
			mLights.push_back(light);

			light = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisSpotlight>();
			light->SetCenter({ 1190.2592, -9.408161, 0 });
			light->RotateClockWise();
			light->SetStartAngle(210);
			mLights.push_back(light);

			light = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisSpotlight>();
			light->SetCenter({ 1931.6791, -14.669791, 0 });
			light->RotateCounterClockWise();
			light->SetStartAngle(90);
			mLights.push_back(light);

			light = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisSpotlight>();
			light->SetCenter({ 2621.489, 140.8391, 0 });
			light->RotateCounterClockWise();
			light->SetStartAngle(290);
			mLights.push_back(light);

			light = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisSpotlight>();
			light->SetCenter({ 3122.3633, 74.33054, 0 });
			light->RotateClockWise();
			light->SetStartAngle(-100);
			mLights.push_back(light);

			light = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisSpotlight>();
			light->SetCenter({ 3837.9368, 80.56461, 0 });
			light->RotateClockWise();
			light->SetStartAngle(15);
			mLights.push_back(light);
		}
		/*
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
		*/
	}
	void TryThisManager::Update()
	{
		double time = mMusic->GetTime();
		CameraMove(time);
		CameraBump(time);
		Light(time);
		MusicManager::Update();
	}
	void TryThisManager::Play()
	{
		mStage->DeActivate();
		mScopeFlag = 0;
		mCameraFlag = 0;
		mLightFlag = 0;
		Vector3 pos = SceneManager::MainCamera()->Owner()->mTransform->GetPosition();
		pos.x = 0;
		pos.y = 0;
		SceneManager::MainCamera()->Owner()->mTransform->SetPosition(pos);

		MusicManager::Play();
	}
	void TryThisManager::OnMusicEnd()
	{
		mMusic->Finish();
		mbFin = true;
	}
	void TryThisManager::CameraMove(double time)
	{
		auto transform = SceneManager::MainCamera()->Owner()->mTransform;
		Vector3 pos = transform->GetPosition();
		if (22.200 <= time && time <= 28.950)
		{
			float t = (time - 22.200) / (28.950 - 22.200);
			float x = LERP(0, 921.45526, t);
			pos.x = x;
			transform->SetPosition(pos);
		}
		else if (33.100 <= time && time <= 56.600) //56.600Àº 
		{
			float t = (time - 33.100) / (56.600 - 33.100);
			float x = LERP(921.45526, 4500, t);
			pos.x = x;
			transform->SetPosition(pos);
		}
		else if (56.600 <= time && time <= 64.050)
		{
			float t = (time - 56.600) / (64.050 - 56.600);
			float x = LERP(4500, 5234.5376, t);
			pos.x = x;
			transform->SetPosition(pos);
		}
	}
	void TryThisManager::CameraBump(double time)
	{
		static double beat[] = {2.95, 3.425, 3.9, 5.55, 6.075, 6.6, 8.4, 8.572, 8.744, 8.916, 9.088, 9.259, 9.431, 9.603, 9.775, 9.947, 10.119
		,10.291, 10.463, 10.634, 10.806, 10.978, 11.15, 11.2, 11.3, 22.15, 22.85, 23.5, 24.1, 24.9, 25.6, 26.3, 26.95, 27.7, 28.4, 29.05, 29.7, 30.4
		, 31.05, 31.75, 32.45, 33.1, 33.85, 34.55, 35.25, 35.95, 36.65, 37.4, 38.05, 38.8, 39.45, 40.15, 40.75, 41.45, 42.15, 42.8, 43.5, 44.15, 67.8
		, 68.4, 69.05, 69.7, 70.4, 71.1, 72.7, 73.2, 73.9, 74.55, 75.25, 75.9, 76.55, 77.3, 78, 78.65, 79.35, 80.15, 80.8, 81.5, 82.1, 82.9, 83.55, 84.25
		, 84.9, 85.6, 86.25, 86.95, 87.7, 88.3, 89.05, 89.7, 90.45, 91.1, 91.8, 92.45, 93.15, 93.85, 94.55, 95.2, 96 , 96.65 , 97.3, 98, 98.7, 99.35, 100.1
		, 100.8, 101.45, 102.1, 102.8, 103.4, 104.2, 104.9, 105.55, 106.25, 107, 107.65
		};
		static Vector3 dir[] = {Vector3::Up, Vector3::Down, Vector3::Left, Vector3::Right};
		static int dirIdx[] = { 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0
		, 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 
		, 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0 , 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, };

		if (mCameraFlag < 116 && time >= beat[mCameraFlag])
		{
			mEffect->Bump(dir[dirIdx[mCameraFlag]]);
			if (mCameraFlag == 3)
				mScope->SetPosition(Vector3::Left * 300);
			else if (mCameraFlag == 7)
				mScope->SetPosition(Vector3::Left * 150);
			else if (mCameraFlag == 24)
				ActivateStage();
			mCameraFlag++;
		}
	}
	void TryThisManager::Light(double time)
	{
		static double beat[] = {
			13.45, 13.6, 13.75, 13.9, 16.25, 16.6, 18.9, 19.05, 19.2, 19.35, 24.5, 24.65, 24.8, 24.95, 27.35, 27.65, 29.85, 30, 30.15, 30.3, 33.2, 
			35.5, 35.65, 35.8, 35.95, 38.5, 38.8, 40.95, 41.133, 41.317, 41.5, 44.3, 44.6, 47.1, 47.4, 49.9, 50.2, 52.65, 52.95, 54.1, 54.4
		};
		static double warning[] = {	2, 2, 0, 0, 2, 0, 2, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 2, 0, 0, 2, 0, 2, 2, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0, 1, 0 };
		static double outro[] = {
			0.162, 0.150, 0.499, 0.346, 0.619, 0.526, 0.162, 0.150, 1.576, 1.433, 0.162, 0.15, 0.499, 0.346, 0.499, 0.597, 0.162, 0.15, 0.499, 0.346, 0.597, 0.162
			, 0.15, 0.499, 0.346, 0.499, 0.597, 0.162, 0.15, 0.499, 0.346, 0.499, 0.597, 0.499, 0.597, 0.499, 0.597, 0.499, 0.597, 0.499, 0.597
		};
		static std::vector<std::vector<int>> idxs = {
			 {0}, {1}, {0}, {1}, {0, 1},  {0, 1}, {0}, {1}, {0}, {1}
			 , {1, 2}, {0, 3}, {1, 2}
		};
		if (mLightFlag < 10 && time >= beat[mLightFlag] - warning[mLightFlag] - 0.2)
		{
			for (int i = 0; i < idxs[mLightFlag].size(); i++)
			{
				mLights[idxs[mLightFlag][i]]->SetTimeline(mMusic, warning[mLightFlag], beat[mLightFlag], outro[mLightFlag]);
			}
			mLightFlag++;
		}
	}
	void TryThisManager::ActivateStage()
	{
		mStage->Activate();
		for (int i = 0; i < 7; i++)
			mLights[i]->Owner()->SetActive(true);
	}
}