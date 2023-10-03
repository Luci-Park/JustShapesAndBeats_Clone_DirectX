#include "TryThisScene.h"
#include "LCamera.h"
#include "LObject.h"
#include "LCollisionManager.h"
#include "PlayerPrefab.h"
#include "CameraScript.h"
#include "TryThisMusicController.h"
namespace lu::JSAB
{
	void TryThisScene::Initialize()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BulletInteractor, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::BulletInteractor, true);

		auto c = object::Instantiate<GameObject>(eLayerType::Camera)->AddComponent<GameCamera>();
		mBackground = c->GetBackground();

		GameObject* manager = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::System);
		manager->SetName(L"TryThisManager");
		manager->AddComponent<TryThisMusicController>();
		mManager = manager->AddComponent<TryThisManager>();


		object::Instantiate<PlayerPrefab>(Vector3(-540, 0, -5), eLayerType::Player);
	}
	void TryThisScene::Update()
	{
		Scene::Update();
	}
	void TryThisScene::OnEnter()
	{
		mManager->Play();
		mBackground->SetBackground(BackgroundScript::eBackgrounds::BLACK);
	}
	void TryThisScene::OnExit()
	{
	}
}