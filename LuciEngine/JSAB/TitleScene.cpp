#include "TitleScene.h"
#include "LRenderer.h"
#include "LObject.h"
#include "LCamera.h"
#include "LGameObject.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"
#include "PlayerPrefab.h"
#include "BackgroundObject.h"
#include "SplashAnimation.h"
#include "OpeningUIObjects.h"
#include "TitleObject.h"

namespace lu::JSAB::Title
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		{
			GameObject* camera = object::Instantiate<GameObject>(eLayerType::Camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			for (int i = 0; i < (UINT)eLayerType::End; i++)
			{
				if (i == (UINT)eLayerType::UI)
					continue;
				cameraComp->TurnLayerMask((eLayerType)i, false);
			}
		}
		object::Instantiate<GameObject>(eLayerType::UI)->AddComponent<SplashAnimation>();
		//BackgroundObject* bg = object::Instantiate<BackgroundObject>(eLayerType::UI);
		//mbgs = bg->GetComponent<BackgroundScript>();

		Scene::Initialize();

	}
	void TitleScene::Update()
	{
		Scene::Update();
	}
	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
		//mbgs->SetBackground(BackgroundScript::Backgrounds::TITLE);
	}
}
