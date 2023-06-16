#include "LSceneManager.h"
#include "LPlayScene.h"
namespace lu
{
	Scene* SceneManager::mActiveScene = nullptr;
	void SceneManager::Initialize()
	{
		mActiveScene = new PlayScene();
		mActiveScene->Initialize();
	}
	void SceneManager::Update()
	{
		if (mActiveScene != nullptr)
			mActiveScene->Update();
	}
	void SceneManager::LateUpdate()
	{
		if (mActiveScene != nullptr)
			mActiveScene->LateUpdate();
	}
	void SceneManager::Render()
	{
		if (mActiveScene != nullptr)
			mActiveScene->Render();
	}
}