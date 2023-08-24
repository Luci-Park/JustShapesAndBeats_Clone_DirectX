#include "TutorialScene.h"
#include "PlayerPrefab.h"
#include "LCamera.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"
#include "TrianglePrefab.h"
#include "TutorialBulletPrefabs.h"
#include "TutorialMusicController.h"
#include "LObject.h"
#include "yaCameraScript.h"

namespace lu::JSAB::Tutorial
{
	void TutorialScene::Initialize()
	{
		GameObject* manager = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::System);
		manager->SetName(L"TutorialManager");
		/*auto m = manager->AddComponent<TutorialMusicController>();
		m->Play();*/
		
		object::Instantiate<PlayerPrefab>(eLayerType::Player);
		//object::Instantiate<TutorialEightBulletsPrefab>(eLayerType::Bullet)->AddComponent<gui::TransformWidget>();
		//object::Instantiate<TutorialBurstBulletsPrefab>(eLayerType::Bullet);
		//object::Instantiate<TutorialBeatBulletsPrefab>(eLayerType::Bullet);
		//object::Instantiate<TutorialRoundBulletsPrefab>(eLayerType::Bullet);

		/*GameObject* pieces = new Pieces;
		pieces->AddComponent<gui::TransformWidget>();
		AddGameObject(eLayerType::Player, pieces);
		EightSideBullet* bullet1, *bullet2, *bullet3, *bullet4;
		bullet1 = new EightSideBullet();
		bullet1->mTransform->SetPosition(Vector3(500, -51, 0));
		bullet1->mTransform->SetScale(Vector3(42, 42, 1));
		AddGameObject(eLayerType::Bullet, bullet1);

		bullet2 = new EightSideBullet();
		bullet2->mTransform->SetPosition(Vector3(500, 41, 0));
		bullet2->mTransform->SetScale(Vector3(42, 42, 1));
		AddGameObject(eLayerType::Bullet, bullet2);

		bullet3 = new EightSideBullet();
		bullet3->mTransform->SetPosition(Vector3(500, 230, 0));
		bullet3->mTransform->SetScale(Vector3(42, 42, 1));
		AddGameObject(eLayerType::Bullet, bullet3);

		bullet4 = new EightSideBullet();
		bullet4->mTransform->SetPosition(Vector3(500, -230, 0));
		bullet4->mTransform->SetScale(Vector3(42, 42, 1));
		AddGameObject(eLayerType::Bullet, bullet4);
		*/


		//Camera
		{
			bool active[]{ true, true, false, true, false };
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			for (int i = 0; i < (UINT)eLayerType::End; i++)
			{
				cameraComp->TurnLayerMask((eLayerType)i, active[i]);
			}
			camera->AddComponent<CameraScript>();
		}
		Scene::Initialize();
	}
	void TutorialScene::Update()
	{
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
