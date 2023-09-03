#include "TitleScene.h"
#include "PlayerPrefab.h"
#include "LCamera.h"
#include "BackgroundObject.h"
#include "OpeningUIObjects.h"
#include "TitleObject.h"
#include "LRenderer.h"
#include "LObject.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"

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
		BackgroundObject* bg = object::Instantiate<BackgroundObject>(eLayerType::UI);		
		object::Instantiate<ShapesObject>(eLayerType::UI);
		object::Instantiate<AndObject>(eLayerType::UI);
		object::Instantiate<BeatsObject>(eLayerType::UI);
		object::Instantiate<LightCircleObject>(eLayerType::UI);
		object::Instantiate<Menu::TitleObject>(eLayerType::UI);
		//Camera
		{
			GameObject* camera = object::Instantiate<BeatsObject>(eLayerType::Camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			for (int i = 0; i < (UINT)eLayerType::End; i++)
			{
				if (i == (UINT)eLayerType::UI)
					continue;
				cameraComp->TurnLayerMask((eLayerType)i, false);
			}
		}

		Scene::Initialize();
		mbgs = bg->GetComponent<BackgroundScript>();

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
		mbgs->SetBackground(BackgroundScript::Backgrounds::TITLE);
		Scene::OnEnter();
	}
}
