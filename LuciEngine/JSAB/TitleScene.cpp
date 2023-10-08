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
#include "LText.h"
#include "LSceneManager.h"
#include "..\\Editor_SOURCE\TransformWidget.h"

namespace lu::JSAB::Title
{
	TitleScene::TitleScene()
		: mbIsInMenu(false)
		, mbTitleEntered(false)
		, mButtons(3)
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
			camera->mTransform->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			mCamera = camera->AddComponent<CameraEffectScript>();
			Camera* cameraComp = camera->AddComponent<Camera>();
			for (int i = 0; i < (UINT)eLayerType::End; i++)
			{
				if (i == (UINT)eLayerType::UI)
					continue;
				cameraComp->TurnLayerMask((eLayerType)i, false);
			}
		}

		mbgs = object::Instantiate<GameObject>(eLayerType::UI)->AddComponent<BackgroundScript>();
		mbgs->Owner()->SetName(L"TitleBackground");
		mTitle = object::Instantiate<TitleObject>(eLayerType::UI);
		float y = 170;
		float step = 120;
		for (int i = 0; i < 3; i++)
		{
			mButtons[i] = object::Instantiate<MenuButtonObject>(eLayerType::UI);
			mButtons[i]->SetActive(false);
			mButtons[i]->mTransform->SetPosition({ 0, y - step * i, 0 });
			mButtons[i]->OffFocus();
		}
		mButtons[0]->SetScene(L"TutorialScene", L"TutorialScene", { -240, -380 });
		mButtons[1]->SetScene(L"DubwooferSubstepScene", L"Dubwoofer", { -260, -380 + 120 * 2 });
		mButtons[2]->SetScene(L"TryThisScene", L"Try This", { -240, -380 + 120 * 4 });
		mBtnIdx = 0;

		mbgm = object::Instantiate<GameObject>(eLayerType::System)->AddComponent<AudioSource>();
		mbgm->Owner()->SetName(L"TitleBGM");
		mAudios[0] = Resources::Find<AudioClip>(L"SFX_INTRO_LOOP");
		mAudios[1] = Resources::Find<AudioClip>(L"mus_jsbtheme");
		mAudios[2] = Resources::Find<AudioClip>(L"SFX_INTRO_STINGER");

		{
			mText = object::Instantiate<GameObject>(eLayerType::UI)->AddComponent<Animator>();
			auto t = mText->Owner()->AddComponent<Text>();
			t->text = L"Let's Go";
			t->size = 100;
			t->offset.x = -160;
			t->offset.y = -50;
			t->color = Color(48 / 255.f, 249 / 255.f, 246 / 255.f, 1);
			auto a = mText->CreateAnimation(L"Appear");
			a->AddScaleKey(0, {5.4, 5.4, 1});
			a->AddScaleKey(0.25, { 1, 1, 1 });
			a->AddPositionKey(0, { -727.8, -487.7, -9.5 });
			a->AddPositionKey(0.25, { -34.3, -42.5, -9.5 });
			a->AddPositionXKey(2, 0);
			a->AddPositionXKey(2.3, 900);
			a->AddFunctionKey(2.5, std::bind(&TitleScene::MoveToScene, this));
			t->SetActive(false);
		}
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
				mbgs->SetBackground(BackgroundScript::eBackgrounds::TITLEGREEN);
				mTitle->OnBeat();
				mbTitleEntered = true;
			}
			if (mbgm->GetClip() == mAudios[1])
			{
				if (Input::GetKeyDown(eKeyCode::ENTER))
				{
					mTitle->OnMove();
					mbIsInMenu = true;
					for (int i = 0; i < 3; i++)
						mButtons[i]->Show();
					mButtons[mBtnIdx]->OnFocus();
				}
			}
		}
		else
		{
			if (Input::GetKeyDown(eKeyCode::UP))
			{
				mbgm->PlayOneShot(Resources::Find<AudioClip>(L"SFX_UI_MOVE_2"), 1);
				mButtons[mBtnIdx]->OffFocus();
				mBtnIdx--;
				if (mBtnIdx < 0) mBtnIdx = 2;
				mButtons[mBtnIdx]->OnFocus();
			}
			else if (Input::GetKeyDown(eKeyCode::DOWN))
			{
				mbgm->PlayOneShot(Resources::Find<AudioClip>(L"SFX_UI_MOVE_2"), 1);
				mButtons[mBtnIdx]->OffFocus();
				++mBtnIdx %= mButtons.size();
				mButtons[mBtnIdx]->OnFocus();
			}
			if (Input::GetKeyDown(eKeyCode::ENTER))
			{
				mbgm->Stop();
				mbgm->SetClip(mAudios[2]);
				mbgm->Play(false);
				mbgm->PlayOneShot(Resources::Find<AudioClip>(L"SFX_HEX_CHALLENGE_RIBBON_TO_COIN"), 1);
				for (int i = 0; i < 3; i++)
					mButtons[i]->Hide();
				mCamera->BlackFadeOut();
				mText->Owner()->SetActive(true);
				mText->PlayAnimation(L"Appear", false);
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
		mCamera->Reset();
		mCamera->mTransform->SetPosition({ 0, 0, -10 });
		if (!mbTitleEntered)
		{
			ShowTitle();
		}
		else
		{
			ShowMenu();
		}
	}
	void TitleScene::StartMusic()
	{
	}
	void TitleScene::ShowTitle()
	{
		mbIsInMenu = false;
		mbgs->SetBackground(BackgroundScript::eBackgrounds::TITLE);
		mbgm->SetClip(mAudios[0]);
		mbgm->Play(false);
		mTitle->OnAppear();
		for (int i = 0; i < 3; i++)
			mButtons[i]->SetActive(false);
	}
	void TitleScene::ShowMenu()
	{
		mbgm->SetClip(mAudios[1]);
		mbgm->Play(true);
		mbgs->SetBackground(BackgroundScript::eBackgrounds::TITLEGREEN);

		mTitle->OnMenu();
		mbIsInMenu = true;
		for (int i = 0; i < 3; i++)
		{
			mButtons[i]->ShowWithOutAnim();
			mButtons[i]->OffFocus();
		}
		mButtons[mBtnIdx]->OnFocus();
	}
	void TitleScene::MoveToScene()
	{
		mButtons[mBtnIdx]->Activate();
	}
	void TitleScene::OnExit()
	{
		mbgm->Stop();
	}
}
