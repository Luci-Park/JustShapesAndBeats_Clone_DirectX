#include "MenuScene.h"
#include "TitleObject.h"
#include "LCamera.h"
#include "BackgroundObject.h"
#include "BackgroundScript.h"
#include "MenuButtonObject.h"
namespace lu::JSAB::Menu
{
	void MenuScene::Initialize()
	{
		BackgroundObject* bg = new BackgroundObject();
		AddGameObject(eLayerType::UI, bg);
		TitleObject* title = new TitleObject();
		AddGameObject(eLayerType::UI, title);
		AddGameObject(eLayerType::UI, new Menu::MenuButtonObject());
		//Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			for (int i = 0; i < (UINT)eLayerType::End; i++)
			{
				if (i == (UINT)eLayerType::UI)
					continue;
				cameraComp->TurnLayerMask((eLayerType)i, false);
			}
		}
		Scene::Initialize();
		
		title->mTransform->SetPosition(Vector3(-60, 0, 0));
		bg->SetBackground(BackgroundScript::Backgrounds::SKYBLUE);
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