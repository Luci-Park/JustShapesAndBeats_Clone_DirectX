#pragma once
#include "..\\Engine_SOURCE\LSceneManager.h"
#include "yaPlayScene.h"
#include "TitleScene.h"
#include "TutorialScene.h"
#include "TestScene.h"
#include "SubstepScene.h"

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
		//SceneManager::CreateScene<Title::TitleScene>(L"TitleScene");
		SceneManager::CreateScene<Tutorial::TutorialScene>(L"TutorialScene");
		//SceneManager::CreateScene<ParticleTestScene>(L"ParticleTestScene");
		//SceneManager::CreateScene<CameraTestScene>(L"CameraTestScene");
		SceneManager::LoadScene(L"TutorialScene");
		//SceneManager::CreateScene<TriangleTestScene>(L"TriangleTestScene");
		//SceneManager::CreateScene<FakeTutorialScene>(L"FakeTutorialScene");
	}
}