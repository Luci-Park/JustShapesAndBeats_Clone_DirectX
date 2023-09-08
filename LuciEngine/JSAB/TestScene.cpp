#include "TestScene.h"
#include "LObject.h"
#include "PlayerPrefab.h"
#include "LParticleSystem.h"
#include "LResources.h"
#include "LCamera.h"
namespace lu::JSAB
{
	TestScene::TestScene()
	{
	}
	TestScene::~TestScene()
	{
	}
	void TestScene::Initialize()
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
		p->RateOverDistance = 5;


		p->SetLifeTime(2);
		p->SetSize(10, 0);
		p->SetTint({ 1, 1, 1, 0.5 }, { 0, 0, 1, 0.5 });
		p->SetWorldSpace(ParticleSystem::Space::world);
		p->SetGravity(0);
		p->SetStartSpeed(20);
		p->Play();

	}
}