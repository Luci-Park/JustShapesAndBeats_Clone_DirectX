#include "LPlayScene.h"
#include "LMeshRenderer.h"
namespace lu
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		Scene::Initialize();
		GameObject* player = new GameObject();
		AddGameObject(eLayerType::Player, player);
		player->AddComponent<MeshRenderer>();
	}
	void PlayScene::Update()
	{
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void PlayScene::Render()
	{
		Scene::Render();
	}
}