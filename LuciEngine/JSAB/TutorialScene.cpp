#include "TutorialScene.h"
#include "PlayerPrefab.h"
#include "LCamera.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"
#include "TrianglePrefab.h"
#include "TutorialMusicController.h"
#include "TutorialManager.h"
#include "TutorialBeatCircle.h"
#include "LObject.h"
#include "LInput.h"
#include "CameraScript.h"

namespace lu::JSAB::Tutorial
{
	CameraScript* cs;
	TutorialBeatCircle* bullet;
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
			cs = camera->AddComponent<CameraScript>();
		}

		//GameObject* manager = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::System);
		//manager->SetName(L"TutorialManager");
		//auto ma = manager->AddComponent<TutorialManager>();
		//auto m = manager->AddComponent<TutorialMusicController>();
		//ma->SetMusic(m);
		//m->Play();
		bullet = object::Instantiate<GameObject>(eLayerType::Bullet)->AddComponent<TutorialBeatCircle>();
		//bullet->Owner()->AddComponent<gui::TransformWidget>();
		object::Instantiate<PlayerPrefab>(eLayerType::Player);

		Scene::Initialize();
	}
	void TutorialScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::W))
			cs->BeatUp();

		if (Input::GetKeyDown(eKeyCode::S))
			cs->BeatDown();

		if (Input::GetKeyDown(eKeyCode::A))
			cs->BeatLeft();

		if (Input::GetKeyDown(eKeyCode::D))
			cs->BeatRight();

		if (Input::GetKeyDown(eKeyCode::F))
			cs->Flash();

		if (Input::GetKeyDown(eKeyCode::O))
			bullet->Show();
		if (Input::GetKeyDown(eKeyCode::P))
			bullet->Activate();
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
