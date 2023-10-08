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

		mCheckPoint = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<CheckPoint>();
		mCheckPoint->SetBackground(SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetBackground());
		mCheckPoint->SetManager(this);

		mScope = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisScope>();
		mScope->SetTimeline(mMusic, 0, .850, 11.3 - .850);

		mStage = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<TryThisStage>();
		for (int i = 0; i < 4; i++)
		{
			auto light = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisSpotlight>();
			mLights.push_back(light);
		}
		/*
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
		*/
	}
	void TryThisManager::Update()
	{
		double time = mMusic->GetTime();
		Camera(time);
		MusicManager::Update();
	}
	void TryThisManager::Play()
	{
		mStage->DeActivate();
		mbScopeFlag = 0;
		mbCameraFlag = 0;
		MusicManager::Play();
	}
	void TryThisManager::OnMusicEnd()
	{
		mMusic->Finish();
		mbFin = true;
	}
	void TryThisManager::Scope(float time)
	{
	}
	void TryThisManager::Camera(float time)
	{
		static double beat[] = {2.95, 3.425, 3.9, 5.55, 6.075, 6.6, 8.4, 8.572, 8.744, 8.916, 9.088, 9.259, 9.431, 9.603, 9.775, 9.947, 10.119
		,10.291, 10.463, 10.634, 10.806, 10.978, 11.15, 11.2, 11.3 
		};
		static Vector3 dir[] = {Vector3::Up, Vector3::Down, Vector3::Left, Vector3::Right};
		static int dirIdx[] = { 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 0 };

		if (mbCameraFlag < 25 && time >= beat[mbCameraFlag])
		{
			mEffect->Bump(dir[dirIdx[mbCameraFlag]]);
			if (mbCameraFlag == 3)
				mScope->SetPosition(Vector3::Left * 300);
			else if (mbCameraFlag == 7)
				mScope->SetPosition(Vector3::Right * 0);
			else if (mbCameraFlag == 24)
				ActivateStage();
			mbCameraFlag++;
		}
	}
	void TryThisManager::ActivateStage()
	{
		mStage->Activate();
		mLights[0]->Owner()->SetActive(true);
		mLights[0]->SetTimeline(mMusic, 2, 13.45, .162);
		mLights[0]->SetCenter({ -264.864, 0, 0 });
		mLights[0]->RotateClockWise();
		mLights[0]->SetStartAngle(210);
		mLights[1]->Owner()->SetActive(true);
		mLights[1]->SetTimeline(mMusic, 2, 13.6, .150);
		mLights[1]->Warning();
		mLights[1]->SetCenter({ 264.864, 0, 0 });
		mLights[1]->RotateCounterClockWise();
	}
}