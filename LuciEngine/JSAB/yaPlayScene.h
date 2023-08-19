#pragma once
#include "..\Engine_SOURCE\LScene.h"
namespace lu
{
	class AudioSource;
	class PlayScene : public Scene
	{
	public:
		PlayScene();
		virtual ~PlayScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		AudioSource* as;
	};
}


