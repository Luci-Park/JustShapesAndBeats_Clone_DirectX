#include "TutorialScene.h"
#include "PlayerPrefab.h"
#include "PlayerPieces.h"
#include "CameraScript.h"
#include "TutorialMusicController.h"
#include "TutorialManager.h"
#include "Triangle.h"
#include "TrianglePrefab.h"

#include "LCamera.h"
#include "LObject.h"
#include "LCollisionManager.h"
#include "LTime.h"
namespace lu::JSAB::Tutorial
{
	void TutorialScene::Initialize()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
		object::Instantiate<GameObject>(eLayerType::Camera)->AddComponent<GameCamera>();

		GameObject* manager = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::System);
		manager->SetName(L"TutorialManager");
		mMusic = manager->AddComponent<TutorialMusicController>();
		mManager = manager->AddComponent<TutorialManager>();
		
		mPlayer = object::Instantiate<PlayerPrefab>(Vector3(0, 0, -5), eLayerType::Player);
		mPlayer->SetActive(false);
		mOpening = object::Instantiate<GameObject>(eLayerType::System)->AddComponent<PlayerPieces>();
		mTriangle = object::Instantiate<TrianglePrefab>(eLayerType::Item)->GetComponent<InGameTriangle>();
		mTriangle->Owner()->SetActive(false);

		mManager->SetTriangle(mTriangle);
		Scene::Initialize(); 
	}
	void TutorialScene::Update()
	{
		mTime += Time::DeltaTime();
		if (mTime >= 3 && !mTriFlag)
		{
			mTriangle->Appear();
			mTriFlag = true;
		}
		Scene::Update();
	}

	void TutorialScene::OnEnter()
	{
		mOpening->Activate(std::bind(&TutorialScene::OnActivate, this));
		mTriangle->SetStrategy(TriangleStrategy::eTriangleStrategyType::PrevTutorial);
		mTime = -1000;
		MusicManager::Instance = mManager;
	}

	void TutorialScene::OnExit()
	{
		mMusic->Stop();
	}
	void TutorialScene::OnActivate()
	{
		mainCamera->Owner()->GetComponent<GameCamera>()->GetEffect()->WhiteFadeIn();
		mPlayer->SetActive(true);
		mTime = 0;
		mTriFlag = false;
	}
}
