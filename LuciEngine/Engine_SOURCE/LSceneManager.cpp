#include "LSceneManager.h"
#include "LPlayScene.h"
#include "JSABScenes.h"
namespace lu
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;
	void SceneManager::Initialize()
	{
		mScenes.insert(std::make_pair(L"Play", new PlayScene()));/*
		mScenes.insert(std::make_pair(L"Menu", new JSAB::MenuScene()));
		mScenes.insert(std::make_pair(L"Tutorial", new JSAB::TutorialScene()));
		mScenes.insert(std::make_pair(L"Overworld", new JSAB::OverworldScene()));
		mScenes.insert(std::make_pair(L"Dubwoofer", new JSAB::DubwooferScene()));
		mScenes.insert(std::make_pair(L"CoolFriends", new JSAB::CoolFriendsScene()));
		mScenes.insert(std::make_pair(L"TryThis", new JSAB::TryThisScene()));
		mScenes.insert(std::make_pair(L"Annhilate", new JSAB::AnnhilateScene()));*/

		for (auto it = mScenes.begin(); it != mScenes.end(); it++)
		{
			it->second->Initialize();
		}
		LoadScene(L"Play");
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
	
	void SceneManager::Release()
	{
		for (auto it : mScenes)
		{
			delete it.second;
			it.second = nullptr;
		}
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
}