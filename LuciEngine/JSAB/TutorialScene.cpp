#include "TutorialScene.h"
#include "PlayerPrefab.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"
#include "CameraScript.h"
#include "TrianglePrefab.h"
#include "TutorialMusicController.h"
#include "TutorialManager.h"
#include "LCamera.h"
#include "LObject.h"
#include "LInput.h"
#include "LCollisionManager.h"

namespace lu::JSAB::Tutorial
{
	CameraScript* burst;
	TutorialFullBar* b;
	void TutorialScene::Initialize()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
		//Camera
		{
			bool active[]{ true, true, true, true, false, false };
			GameObject* camera = object::Instantiate<GameObject>(eLayerType::Camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			for (int i = 0; i < (UINT)eLayerType::End; i++)
			{
				cameraComp->TurnLayerMask((eLayerType)i, active[i]);
			}
			burst = camera->AddComponent<CameraScript>();
		}

		GameObject* manager = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::System);
		manager->SetName(L"TutorialManager");
		auto ma = manager->AddComponent<TutorialManager>();
		music = manager->AddComponent<TutorialMusicController>();
		ma->SetMusic(music);		
		object::Instantiate<PlayerPrefab>(eLayerType::Player);
		Scene::Initialize(); 
	}
	void TutorialScene::Update()
	{
		Scene::Update();
	}

	void TutorialScene::OnEnter()
	{
		music->Play();
	}
}
