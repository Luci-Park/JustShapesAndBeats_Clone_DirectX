#include "DubwooferSubstepScene.h"
#include "LCamera.h"
#include "LObject.h"
#include "LCollisionManager.h"
#include "PlayerPrefab.h"
#include "CameraScript.h"
#include "DubwooferManager.h"
#include "DubwooferMusicController.h"
#include "yaCameraScript.h"
namespace lu::JSAB
{
	void DubwooferSubstepScene::Initialize()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BulletInteractor, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::BulletInteractor, true);

		auto c =object::Instantiate<GameObject>(eLayerType::Camera)->AddComponent<GameCamera>();
		mBackground = c->GetBackground();
		//c->Owner()->AddComponent<yaCamera>();

		GameObject* manager = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::System);
		manager->SetName(L"DubwooferManager");
		manager->AddComponent<DubwooferMusicController>();
		mManager = manager->AddComponent<DubwooferManager>();

		
		mPlayer = object::Instantiate<PlayerPrefab>(Vector3(-540, 0, -5), eLayerType::Player);
	}
	void DubwooferSubstepScene::Update()
	{
		Scene::Update();
	}
	void DubwooferSubstepScene::OnEnter()
	{
		mPlayer->SetActive(true);
		mPlayer->mTransform->SetPosition(Vector3(-540, 0, -5));
		mManager->Play();
		mBackground->SetBackground(BackgroundScript::eBackgrounds::BLACK);
	}
	void DubwooferSubstepScene::OnExit()
	{
	}
}