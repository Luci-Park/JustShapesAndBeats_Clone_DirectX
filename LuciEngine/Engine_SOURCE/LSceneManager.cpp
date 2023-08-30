#include "LSceneManager.h"
namespace lu
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;
	void SceneManager::Initialize()
	{

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

	void SceneManager::Destroy()
	{
		if (mActiveScene != nullptr)
			mActiveScene->Destroy();
	}
	
	void SceneManager::Release()
	{
		for (auto it : mScenes)
		{
			delete it.second;
			it.second = nullptr;
		}
	}

	Scene* SceneManager::GetScene(std::wstring name)
	{
		auto it = mScenes.find(name);
		if (it == mScenes.end())
			return nullptr;
		else return it->second;
	}

	Scene* SceneManager::LoadScene(std::wstring name)
	{
		auto it = mScenes.find(name);
		if (it == mScenes.end())
			return nullptr;
		if(mActiveScene != nullptr)
			mActiveScene->OnExit();
		mActiveScene = it->second;
		mActiveScene->OnEnter();
		return it->second;
	}
	void SceneManager::AddCamera(Camera* camera)
	{
		mActiveScene->AddCamera(camera);
	}
	Camera* SceneManager::MainCamera()
	{
		return mActiveScene->mainCamera;
	}
}