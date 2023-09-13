#pragma once
#include "..\Engine_SOURCE\LScene.h"
namespace lu
{
	class AudioSource;
	class AudioClip;
	class GameObject;
}
namespace lu::JSAB
{
	class BackgroundScript;
	class TitleObject;
	class MenuButtonObject;
	class CameraScript;
}
namespace lu::JSAB::Title
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
		void StartMusic();
	private:
		BackgroundScript* mbgs;
		TitleObject* mTitle;
		AudioSource* mbgm;
		MenuButtonObject* mButton;
		CameraScript* mCamera;
		bool mbIsInMenu;
		std::shared_ptr<AudioClip> mAudios[3];
	};
}

