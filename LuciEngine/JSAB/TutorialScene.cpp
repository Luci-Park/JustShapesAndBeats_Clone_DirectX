#include "TutorialScene.h"
#include "PlayerPrefab.h"
#include "PlayerPieces.h"
#include "CameraScript.h"
#include "TutorialMusicController.h"
#include "TutorialManager.h"

#include "LCamera.h"
#include "LObject.h"
#include "LCollisionManager.h"
namespace lu::JSAB::Tutorial
{
	void TutorialScene::Initialize()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
		object::Instantiate<GameObject>(eLayerType::Camera)->AddComponent<GameCamera>();

		GameObject* manager = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::System);
		manager->SetName(L"TutorialManager");
		music = manager->AddComponent<TutorialMusicController>();
		manager->AddComponent<TutorialManager>();
		
		mPlayer = object::Instantiate<PlayerPrefab>(Vector3(0, 0, -5), eLayerType::Player);
		mPlayer->SetActive(false);
		mOpening = object::Instantiate<GameObject>(eLayerType::Camera)->AddComponent<PlayerPieces>();
		Scene::Initialize(); 
	}
	void TutorialScene::Update()
	{
		Scene::Update();
	}

	void TutorialScene::OnEnter()
	{
		mOpening->Activate(std::bind(&TutorialScene::OnActivate, this));
	}

	void TutorialScene::OnExit()
	{
		music->Stop();
	}
	void TutorialScene::OnActivate()
	{
		mainCamera->Owner()->GetComponent<GameCamera>()->GetEffect()->LevelTrans();
		mPlayer->SetActive(true);
	}
}
