#pragma once
#include "..\\Engine_SOURCE\LSceneManager.h"
#include "LPlayScene.h"
#include "MenuScene.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\JSAB.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\JSAB.lib")
#endif
namespace lu::JSAB
{
	void InitializeScenes()
	{
		//SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<MenuScene>(L"MenuScene");
		SceneManager::LoadScene(L"MenuScene");
	}
}