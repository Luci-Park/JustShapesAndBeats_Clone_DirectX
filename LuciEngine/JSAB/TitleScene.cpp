#include "TitleScene.h"
#include "LRenderer.h"
#include "LObject.h"
#include "LCamera.h"
#include "LGameObject.h"
#include "LAudioSource.h"
#include "LResources.h"
#include "LAnimator.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"
#include "BackgroundScript.h"
#include "SplashAnimation.h"
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
		//auto an = mAnim->Owner()->GetComponent<Animator>();

		mbgs = object::Instantiate<GameObject>(eLayerType::UI)->AddComponent<BackgroundScript>();
		mTitle = object::Instantiate<TitleObject>(eLayerType::UI);

		mbgm = object::Instantiate<GameObject>(eLayerType::System)->AddComponent<AudioSource>();
		mAudios[0] = Resources::Load<AudioClip>(L"ThemeOpening", L"..\\..\\Assets\\AudioClips\\MainMenu\\SFX_INTRO_LOOP.wav");
		mAudios[1] = Resources::Load<AudioClip>(L"Theme", L"..\\..\\Assets\\AudioClips\\MainMenu\\mus_jsbtheme.wav");
		mAudios[2] = Resources::Load<AudioClip>(L"Stinger", L"..\\..\\Assets\\AudioClips\\MainMenu\\SFX_INTRO_STINGER.wav");
		Scene::Initialize();

	}
	void TitleScene::Update()
	{
		if(!mbgm->IsPlaying())
		{
			mbgm->SetClip(mAudios[1]);
			mbgm->Play(true);
			mbgs->SetBackground(BackgroundScript::Backgrounds::TITLEGREEN);
			mTitle->OnBeat();
		}
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
		mbgm->SetClip(mAudios[0]);
		mbgm->Play(false);
		mTitle->OnAppear();
	}
	void TitleScene::StartMusic()
	{
	}
	void TitleScene::OnExit()
	{
		mbgm->Stop();
	}
}
