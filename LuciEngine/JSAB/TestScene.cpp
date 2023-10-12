#include "TestScene.h"
#include "LObject.h"
#include "PlayerPrefab.h"
#include "LParticleSystem.h"
#include "LResources.h"
#include "LCamera.h"
#include "LInput.h"
#include "LText.h"
#include "LCollisionManager.h"
#include "yaCameraScript.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"
#include "TrianglePrefab.h" 
#include "DubwooferSpikeDropper.h"
#include "DubwooferDropSpawner.h"
#include "DubwooferWater.h"
#include "TryThisStage.h"
#include "TryThisRoundSpike.h"
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
		p->SetTexture(Resources::Find<Texture>(L"player1"));
		p->Duration = 5;
		p->MaxParticles = 1000;
		p->Loop = true;
		p->Bursts.push_back({ 0, 10, false});
		p->RateOverTime = 0;
		p->RateOverDistance = 0.5;
		p->SetStartRadius(1);
		p->SetOffset(Vector3::Zero);
		p->SetAngle(-180 + 20, -20);//작은게 먼저
		p->SetLifeTime(3);
		p->SetSize(20, 0);
		p->SetTint({ 1, 1, 1, 0.5 }, { 0, 0, 1, 0.5 });
		p->SetWorldSpace(ParticleSystem::Space::world);
		p->SetGravity(0);
		p->SetStartSpeed(40);
		p->Play();

	}
#pragma endregion

#pragma region CameraTestScene
	void CameraTestScene::Initialize()
	{
		object::Instantiate<GameObject>(eLayerType::Camera)->AddComponent<GameCamera>();
		auto a = object::Instantiate<PlayerPrefab>(eLayerType::Player);

	}
	void CameraTestScene::Update()
	{
		Scene::Update();
	}
	void TriangleTestScene::Initialize()
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
		}
		auto g = object::Instantiate<lu::JSAB::TrianglePrefab>(eLayerType::Item);
		auto a = object::Instantiate<PlayerPrefab>(eLayerType::Player);
		/*auto p = g->AddComponent<ParticleSystem>();
		p->GetMaterial()->SetTexture(Resources::Find<Texture>(L"player1"));
		p->Duration = 10;
		p->MaxParticles = 1000;
		p->Loop = true;
		p->Bursts.push_back({ 0, 30, false });
		p->RateOverTime = 0;
		p->RateOverDistance = 0.5;

		p->SetOffset(Vector3::Zero);
		p->SetAngle(0, 360);
		p->SetLifeTime(2);
		p->SetSize(40, 40);
		p->SetTint({ 0, 0, 0, 0.5 }, { 1, 1, 1, 0.5 });
		p->SetWorldSpace(ParticleSystem::Space::world);
		p->SetGravity(0);
		p->SetStartSpeed(300);
		p->SetRotation(0, 300);
		p->Play();*/
		
	}
	void TriangleTestScene::Update()
	{
		Scene::Update();
	}
#pragma endregion

#pragma region BulletTest
	void BulletTestScene::Initialize()
	{
		auto c = object::Instantiate<GameObject>(eLayerType::Camera)->AddComponent<GameCamera>();
		c->Owner()->AddComponent<yaCamera>();
		c->mTransform->SetPosition(0, 0, -10);
		auto g = object::Instantiate<GameObject>(eLayerType::Bullet);
		script = g->AddComponent<DubwooferWater>();
		g->mTransform->SetPosition(0, -360, 0);
	}

	void BulletTestScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			dynamic_cast<DubwooferWater*>(script)->RippleTest(0);
			//bullet->mTransform->SetPosition({ 0, 0, 0 });
			//bullet->Activate();
			//dynamic_cast<TryThisScope*>(bullet)->SetPosition({-300, 0, 0});
		}
		Scene::Update();
	}
#pragma endregion

}