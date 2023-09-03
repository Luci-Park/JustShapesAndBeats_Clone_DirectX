#include "MenuScene.h"
#include "TitleObject.h"
#include "LCamera.h"
#include "BackgroundObject.h"
#include "BackgroundScript.h"
#include "MenuButtonObject.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"
namespace lu::JSAB::Menu
{
	void MenuScene::Initialize()
	{
		BackgroundObject* bg = new BackgroundObject(eLayerType::UI);
		AddGameObject(eLayerType::UI, bg);
		TitleObject* title = new TitleObject(eLayerType::UI);
		AddGameObject(eLayerType::UI, title);
		title->AddComponent<gui::TransformWidget>();
		AddGameObject(eLayerType::UI, new Menu::MenuButtonObject(eLayerType::UI));
		//Camera
		{
			GameObject* camera = new GameObject(eLayerType::Camera);
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
		
		title->mTransform->SetPosition(Vector3(-281, 0, 0));
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