#include "TestScene.h"
#include "LObject.h"
#include "PlayerPrefab.h"
#include "LParticleSystem.h"
#include "LResources.h"
#include "LCamera.h"
#include "LInput.h"
#include "LText.h"
#include "LCollisionManager.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"
namespace lu::JSAB
{
#pragma region ParticleTestScene


	ParticleTestScene::ParticleTestScene()
	{
	}
	ParticleTestScene::~ParticleTestScene()
	{
	}
	void ParticleTestScene::Initialize()
	{
		{
			bool active[]{ true, true, true, true, false };
			GameObject* camera = object::Instantiate<GameObject>(eLayerType::Camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			for (int i = 0; i < (UINT)eLayerType::End; i++)
			{
				cameraComp->TurnLayerMask((eLayerType)i, active[i]);
			}
		}
		auto a = object::Instantiate<PlayerPrefab>(eLayerType::Player);
		auto p = a->AddComponent<ParticleSystem>();
		p->GetMaterial()->SetTexture(Resources::Find<Texture>(L"player1"));
		p->Duration = 10;
		p->MaxParticles = 1000;
		p->Loop = true;
		//p->Bursts.push_back({ 0, 10, false });
		p->RateOverTime = 0;
		p->RateOverDistance = 0.5;

		p->SetOffset(Vector3::Zero);
		p->SetAngle(60, -60 );
		p->SetLifeTime(1);
		p->SetSize(10, 0);
		p->SetTint({ 1, 1, 1, 0.5 }, { 0, 0, 1, 0.5 });
		p->SetWorldSpace(ParticleSystem::Space::world);
		p->SetGravity(0);
		p->SetStartSpeed(20);
		p->Play();

	}
#pragma endregion

#pragma region CameraTestScene
	void CameraTestScene::Initialize()
	{
		{
			bool active[]{ true, true, true, true, false, false };
			GameObject* camera = object::Instantiate<GameObject>(eLayerType::Camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			for (int i = 0; i < (UINT)eLayerType::End; i++)
			{
				cameraComp->TurnLayerMask((eLayerType)i, active[i]);
			}
			script = camera->AddComponent<GameCamera>();
		}
		auto a = object::Instantiate<PlayerPrefab>(eLayerType::Player);
		auto t = object::Instantiate<GameObject>(eLayerType::UI)->AddComponent<Text>();
		t->color = Color(48/255.f, 249/255.f, 246/255.f, 1);
		t->text = L"Let's Go";
		t->size = 60;
		t->offset.x = -111;
		t->offset.y = -88;
		t->Owner()->AddComponent<gui::TransformWidget>();
	}
	void CameraTestScene::Update()
	{
		/*
		if (Input::GetKeyDown(eKeyCode::W))
			script->Bump(Vector3::Up);
		if (Input::GetKeyDown(eKeyCode::A))
			script->Bump(Vector3::Left);
		if (Input::GetKeyDown(eKeyCode::S))
			script->Bump(Vector3::Down);
		if (Input::GetKeyDown(eKeyCode::D))
			script->Bump(Vector3::Right);

		if (Input::GetKeyDown(eKeyCode::E))
			script->WhiteFlash();
		if (Input::GetKeyDown(eKeyCode::R))
			script->BlackFlash();
		if (Input::GetKeyDown(eKeyCode::V))
			script->BlackFadeOut();*/
		Scene::Update();
	}
#pragma endregion
#include "TutorialMusicController.h"
#include "NewTutorialManager.h"
#pragma region TutorialScene
	
	using namespace lu::JSAB;
	void FakeTutorialScene::Initialize()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Bullet, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Item, true);
		object::Instantiate<GameObject>(eLayerType::Camera)->AddComponent<GameCamera>();

		GameObject* manager = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::System);
		manager->SetName(L"TutorialManager");
		auto m = manager->AddComponent<TutorialMusicController>();
		manager->AddComponent<NewTutorialManager>();
		
		m->Play();
		Scene::Initialize();		
	}

	void FakeTutorialScene::Update()
	{
		Scene::Update();
	}
#pragma endregion

}