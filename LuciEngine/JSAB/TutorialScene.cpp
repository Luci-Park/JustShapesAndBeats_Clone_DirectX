#include "TutorialScene.h"
#include "PlayerPrefab.h"
#include "LTrianglePrefab.h"
#include "LCamera.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"
#include "EightSideBulletPrefabs.h"
namespace lu::JSAB::Tutorial
{
	void TutorialScene::Initialize()
	{
		AddGameObject(eLayerType::Player, new PlayerPrefab());
		AddGameObject(eLayerType::Bullet, new TrianglePrefab());
		AddGameObject(eLayerType::Bullet, new TutorialEightBullets());
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
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Camera, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			for (int i = 0; i < (UINT)eLayerType::End; i++)
			{
				if (i == (UINT)eLayerType::Player|| i == (UINT) eLayerType::Bullet)
					continue;
				cameraComp->TurnLayerMask((eLayerType)i, false);
			}
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
