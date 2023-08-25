#include "TutorialScene.h"
#include "PlayerPrefab.h"
#include "LCamera.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"
#include "TrianglePrefab.h"
#include "TutorialBulletPrefabs.h"
#include "TutorialMusicController.h"
#include "TutorialManager.h"
#include "LObject.h"
#include "yaCameraScript.h"

namespace lu::JSAB::Tutorial
{
	void TutorialScene::Initialize()
	{
		//Camera
		{
			bool active[]{ true, true, false, true, false };
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			for (int i = 0; i < (UINT)eLayerType::End; i++)
			{
				cameraComp->TurnLayerMask((eLayerType)i, active[i]);
			}
			camera->AddComponent<CameraScript>();
		}

		//GameObject* manager = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::System);
		//manager->SetName(L"TutorialManager");
		//auto ma = manager->AddComponent<TutorialManager>();
		//auto m = manager->AddComponent<TutorialMusicController>();
		//ma->SetMusic(m);
		//m->Play();
		
		object::Instantiate<TutorialBeatBulletsPrefab>(eLayerType::Bullet);

		object::Instantiate<PlayerPrefab>(eLayerType::Player);

		Scene::Initialize();
	}
	void TutorialScene::Update()
	{
		Scene::Update();
	}
	void TutorialScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TutorialScene::Render()
	{
		Scene::Render();
	}
}
