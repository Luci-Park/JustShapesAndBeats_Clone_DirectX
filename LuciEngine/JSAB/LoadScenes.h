#pragma once
#include "..\\Engine_SOURCE\LSceneManager.h"
#include "yaPlayScene.h"
#include "TitleScene.h"
#include "MenuScene.h"
#include "TutorialScene.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\JSAB.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\JSAB.lib")
#endif
namespace lu::JSAB
{
	void InitializeScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<Title::TitleScene>(L"TitleScene");
		SceneManager::CreateScene<Menu::MenuScene>(L"MenuScene");
		SceneManager::CreateScene<Tutorial::TutorialScene>(L"TutorialScene");
		SceneManager::LoadScene(L"PlayScene");
	}
}