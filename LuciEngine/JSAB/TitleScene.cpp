#include "TitleScene.h"
#include "PlayerObject.h"
#include "LCamera.h"
#include "CameraScript.h"
#include "BackgroundObject.h"
#include "OpeningUIObjects.h"
#include "TitleObject.h"
#include "LRenderer.h"

namespace lu::JSAB::Title
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		BackgroundObject* bg = new BackgroundObject();
		AddGameObject(eLayerType::UI, bg);
		//AddGameObject(eLayerType::UI, new PlayerObject());
		
		AddGameObject(eLayerType::UI, new ShapesObject());
		AddGameObject(eLayerType::UI, new AndObject());
		AddGameObject(eLayerType::UI, new BeatsObject());
		AddGameObject(eLayerType::UI, new LightCircleObject());

		AddGameObject(eLayerType::UI, new Menu::TitleObject());

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
		mbgs = bg->GetComponent<BackgroundScript>();

	}
	void TitleScene::Update()
	{
		Scene::Update();
	}
	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
		mbgs->SetBackground(BackgroundScript::Backgrounds::TITLE);
		Scene::OnEnter();
	}
}
