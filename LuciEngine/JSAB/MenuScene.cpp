#include "MenuScene.h"
#include "PlayerObject.h"
#include "LCamera.h"
#include "CameraScript.h"
#include "BackgroundObject.h"
#include "OpeningUIObjects.h"

namespace lu::JSAB::MainMenu
{
	MenuScene::MenuScene()
	{
	}
	MenuScene::~MenuScene()
	{
	}
	void MenuScene::Initialize()
	{
		BackgroundObject* bg = new BackgroundObject();
		AddGameObject(eLayerType::UI, bg);
		//AddGameObject(eLayerType::UI, new PlayerObject());
		
		AddGameObject(eLayerType::UI, new ShapesObject());
		AddGameObject(eLayerType::UI, new AndObject());
		AddGameObject(eLayerType::UI, new BeatsObject());

		//Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			//camera->AddComponent<CameraScript>();
		}

		Scene::Initialize();

		bg->SetBackground(BackgroundScript::Backgrounds::TITLE);
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
