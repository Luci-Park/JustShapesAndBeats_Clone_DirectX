#include "MenuScene.h"
#include "TitleObject.h"
namespace lu::JSAB::Menu
{
	void MenuScene::Initialize()
	{
		TitleObject* title = new TitleObject();
		AddGameObject(eLayerType::UI, title);

		Scene::Initialize();
		
		title->mTransform->SetPosition(Vector3(-60, 0, 0));
	}
	void MenuScene::Update()
	{
		Scene::Update();
	}
	void MenuScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void MenuScene::Render()
	{
		Scene::Render();
	}
}