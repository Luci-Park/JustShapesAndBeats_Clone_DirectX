#include "TutorialScene.h"
#include "PlayerPrefab.h"
#include "LCamera.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"
#include "TrianglePrefab.h"
#include "TutorialMusicController.h"
#include "TutorialManager.h"
#include "TutorialBeatBar.h"
#include "TutorialBeatCircle.h"
#include "LObject.h"
#include "LInput.h"
#include "CameraScript.h"

namespace lu::JSAB::Tutorial
{
	CameraScript* burst;
	void TutorialScene::Initialize()
	{
		//Camera
		{
			bool active[]{ true, true, true, true, false };
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			for (int i = 0; i < (UINT)eLayerType::End; i++)
			{
				cameraComp->TurnLayerMask((eLayerType)i, active[i]);
			}
			burst = camera->AddComponent<CameraScript>();
		}

		GameObject* manager = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::System);
		manager->SetName(L"TutorialManager");
		auto ma = manager->AddComponent<TutorialManager>();
		auto m = manager->AddComponent<TutorialMusicController>();
		ma->SetMusic(m);
		m->Play();
		//burst = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<TutorialBeatBar>();

		object::Instantiate<PlayerPrefab>(eLayerType::Player);
		Scene::Initialize(); 
	}
	void TutorialScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::W))
			burst->BeatUp();

		if (Input::GetKeyDown(eKeyCode::S))
			burst->BeatDown();

		if (Input::GetKeyDown(eKeyCode::A))
			burst->BeatLeft();

		if (Input::GetKeyDown(eKeyCode::D))
			burst->BeatRight();

		if (Input::GetKeyDown(eKeyCode::F))
			burst->Flash();
		Scene::Update();
	}
	void TutorialScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TutorialScene::Render()
	{
		Scene::Render();
	}
}
