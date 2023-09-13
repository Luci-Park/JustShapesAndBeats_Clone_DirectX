#include "TitleScene.h"
#include "LRenderer.h"
#include "LObject.h"
#include "LCamera.h"
#include "LGameObject.h"
#include "LAudioSource.h"
#include "LResources.h"
#include "LAnimator.h"
#include "BackgroundScript.h"
#include "SplashAnimation.h"
#include "TitleObject.h"
#include "MenuButtonObject.h"
#include "CameraScript.h"
#include "LInput.h"

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
			camera->SetName(L"TitleScene Camera");
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			mCamera = camera->AddComponent<CameraScript>();
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
		mButton = object::Instantiate<MenuButtonObject>(eLayerType::UI);
		mButton->SetActive(false);

		mbgm = object::Instantiate<GameObject>(eLayerType::System)->AddComponent<AudioSource>();
		mAudios[0] = Resources::Find<AudioClip>(L"SFX_INTRO_LOOP");
		mAudios[1] = Resources::Find<AudioClip>(L"mus_jsbtheme");
		mAudios[2] = Resources::Find<AudioClip>(L"SFX_INTRO_STINGER");
		Scene::Initialize();

	}
	void TitleScene::Update()
	{
		if (!mbIsInMenu)
		{
			if (!mbgm->IsPlaying())
			{
				mbgm->SetClip(mAudios[1]);
				mbgm->Play(true);
				mbgs->SetBackground(BackgroundScript::Backgrounds::TITLEGREEN);
				mTitle->OnBeat();
			}
			if (mbgm->GetClip() == mAudios[1])
			{
				if (Input::GetKeyDown(eKeyCode::ENTER))
				{
					mTitle->OnMove();
					mbIsInMenu = true;
					mButton->SetActive(true);
					mButton->GetComponent<Animator>()->PlayAnimation(L"Appear", false);
				}
			}
		}
		else
		{
			if (Input::GetKeyDown(eKeyCode::ENTER))
			{
				mbgm->Stop();
				mbgm->SetClip(mAudios[2]);
				mbgm->Play(false);
				mbgm->PlayOneShot(Resources::Find<AudioClip>(L"SFX_HEX_CHALLENGE_RIBBON_TO_COIN"), 1);
				mButton->GetComponent<Animator>()->PlayAnimation(L"Disappear", false);
				mCamera->BlackFadeOut();
			}
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
		mbIsInMenu = false;
		mbgs->SetBackground(BackgroundScript::Backgrounds::TITLE);
		mbgm->SetClip(mAudios[0]);
		mbgm->Play(false);
		mTitle->OnAppear();
		mButton->SetActive(false);
		mCamera->Reset();
	}
	void TitleScene::StartMusic()
	{
	}
	void TitleScene::OnExit()
	{
		mbgm->Stop();
	}
}
