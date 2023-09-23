#include "DubwooferSubstepScene.h"
#include "LCamera.h"
#include "LObject.h"
#include "LCollisionManager.h"
#include "PlayerPrefab.h"
#include "CameraScript.h"
#include "DubwooferManager.h"
namespace lu::JSAB
{
	void DubwooferSubstepScene::Initialize()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::BulletInteractor, true);
		CollisionManager::SetLayer(eLayerType::Bullet, eLayerType::BulletInteractor, true);

		object::Instantiate<GameObject>(eLayerType::Camera)->AddComponent<GameCamera>();

		GameObject* manager = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::System);
		manager->SetName(L"DubwooferManager");
		mMusic = manager->AddComponent<MusicController>();
		manager->AddComponent<DubwooferManager>();

		mMusic->SetClip(L"mus_dubwoofer_substep");
		object::Instantiate<PlayerPrefab>(Vector3(-540, 0, -5), eLayerType::Player);
	}
	void DubwooferSubstepScene::Update()
	{
		Scene::Update();
	}
	void DubwooferSubstepScene::OnEnter()
	{
		mMusic->Play();
	}
	void DubwooferSubstepScene::OnExit()
	{
		mMusic->Stop();
	}
}