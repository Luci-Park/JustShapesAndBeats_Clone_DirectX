#include "LPlayScene.h"
#include "LTransform.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "LMesh.h"
#include "CameraScript.h"
#include "LCamera.h"
#include "LSceneManager.h"
#include "BackgroundObject.h"

namespace lu
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		{
			GameObject* player = new GameObject();
			player->SetName(L"Zelda");
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0001f));
			//player->AddComponent<CameraScript>();

			GameObject* player2 = new GameObject();
			player2->SetName(L"ZeldaChild");
			AddGameObject(eLayerType::Player, player2);
			MeshRenderer* mr2 = player2->AddComponent<MeshRenderer>();
			mr2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr2->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
			player2->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 0.0f, 1.0001f));

			player2->GetComponent<Transform>()->SetParent(player->GetComponent<Transform>());
			//player->AddComponent<CameraScript>();

			const float pi = 3.141592f;
			float degree = pi / 2.0f;

			//player->GetComponent<Transform>()->SetPosition(Vector3(-1.0f, 0.0f, 1.0001f));
			player->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree));
		}

		{
			GameObject* player = new GameObject();
			player->SetName(L"Smile");
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
			//player->AddComponent<CameraScript>();
		}

		{
			GameObject* player = new GameObject();
			player->SetName(L"Smile");
			AddGameObject(eLayerType::UI, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.2f, 0.0f, 0.0f));
			//player->AddComponent<CameraScript>();
		}
		{
			JSAB::BackgroundObject* bg = new JSAB::BackgroundObject();
			AddGameObject(eLayerType::UI, bg);
		}

		//Main Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
		}

		//UI Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -50.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			//camera->AddComponent<CameraScript>();
		}

		//GameObject* player2 = new GameObject();
		//AddGameObject(eLayerType::Player, player2);
		//player2->AddComponent<MeshRenderer>();

		//Transform* tr = player->GetComponent<Transform>();
		//tr->SetPosition(Vector3(0.5f, 0.5f, 0.0f));
		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
}