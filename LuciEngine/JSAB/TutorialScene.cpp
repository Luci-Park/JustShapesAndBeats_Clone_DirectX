#include "TutorialScene.h"
#include "PlayerObject.h"
#include "LCamera.h"
namespace lu::JSAB::Tutorial
{
	void TutorialScene::Initialize()
	{
		AddGameObject(eLayerType::Player, new PlayerObject());
		AddGameObject(eLayerType::Player, new Pieces());

		//Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			for (int i = 0; i < (UINT)eLayerType::End; i++)
			{
				if (i == (UINT)eLayerType::Player)
					continue;
				cameraComp->TurnLayerMask((eLayerType)i, false);
			}
		}
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
