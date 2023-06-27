#include "LPlayScene.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "LCameraScript.h"
#include "LTransform.h"
#include "LCamera.h"
#include "BackgroundObject.h"
#include "BackgroundScript.h"
#include "LInput.h"
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
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
			player->GetComponent<Transform>()->SetPos(Vector3(0.0f, 0.0f, 1.0f));
			//player->AddComponent<CameraScript>();
		}

		{
			GameObject* player = new GameObject();
			AddGameObject(eLayerType::Player, player);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			player->GetComponent<Transform>()->SetPos(Vector3(0.2f, 0.0f, 0.0f));
			//player->AddComponent<CameraScript>();
		}
	 
		//Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPos(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();

	/*
		lu::JSAB::BackgroundObject* bg = new lu::JSAB::BackgroundObject;
		AddGameObject(eLayerType::Background, bg);
		bs = bg->AddComponent<JSAB::BackgroundScript>();
		Scene::Initialize();
		bs->SetMaterial(JSAB::BackgroundScript::Backgrounds::ANNIHILATE);*/
	
	}
	void PlayScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			int r = GetRandomInt(0, (int)(JSAB::BackgroundScript::Backgrounds::END)-1);
			bs->SetMaterial(r);
		}
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