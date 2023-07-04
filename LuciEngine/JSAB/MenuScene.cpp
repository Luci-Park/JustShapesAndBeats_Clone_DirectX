#include "MenuScene.h"
#include "PlayerObject.h"
#include "LCamera.h"
#include "CameraScript.h"
#include "BackgroundObject.h"

namespace lu::JSAB
{
	MenuScene::MenuScene()
	{
	}
	MenuScene::~MenuScene()
	{
	}
	void MenuScene::Initialize()
	{
		AddGameObject(eLayerType::Player, new PlayerObject());
		AddGameObject(eLayerType::UI, new BackgroundObject());
		//Main Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
		}
		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			//camera->AddComponent<CameraScript>();
		}

		Scene::Initialize();
	}
	void MenuScene::Update()
	{
		Scene::Update();
	}
	void MenuScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void MenuScene::Render()
	{
		Scene::Render();
	}
}
