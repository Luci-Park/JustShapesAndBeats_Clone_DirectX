#include "TutorialScene.h"
#include "PlayerPrefab.h"
#include "CameraScript.h"
#include "TrianglePrefab.h"
#include "TutorialMusicController.h"
#include "TutorialManager.h"

#include "TutorialBeatCircle.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"

#include "LCamera.h"
#include "LObject.h"
#include "LInput.h"
#include "LCollisionManager.h"
#include "LFontWrapper.h"
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
		
		auto c = object::Instantiate<TrianglePrefab>(Vector3(320.0f, 0.0f, 1.0001f), eLayerType::Item);

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

	void TutorialScene::OnExit()
	{
		music->Stop();
	}
}
