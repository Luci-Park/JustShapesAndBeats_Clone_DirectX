#include "MenuScene.h"
#include "TitleObject.h"
#include "LCamera.h"
#include "LObject.h"
#include "BackgroundScript.h"
#include "MenuButtonObject.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"
namespace lu::JSAB
{
	void MenuScene::Initialize()
	{
		//mbgs = object::Instantiate<GameObject>(eLayerType::UI)->AddComponent<BackgroundScript>();
		TitleObject* title = new TitleObject(eLayerType::UI);
		AddGameObject(eLayerType::UI, title);
		title->AddComponent<gui::TransformWidget>();
		AddGameObject(eLayerType::UI, new MenuButtonObject(eLayerType::UI));
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