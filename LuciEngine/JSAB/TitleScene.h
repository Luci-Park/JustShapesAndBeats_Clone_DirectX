#pragma once
#include "..\Engine_SOURCE\LScene.h"
namespace lu
{
	class AudioSource;
	class AudioClip;
}
namespace lu::JSAB
{
	class BackgroundScript;
	class SplashAnimation;
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

	private:
		BackgroundScript* mbgs;
		SplashAnimation* mAnim;
		AudioSource* mbgm;
		std::shared_ptr<AudioClip> mAudios[3];
	};
}

