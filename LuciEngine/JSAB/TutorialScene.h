#pragma once
#include "..\Engine_SOURCE\LScene.h"

namespace lu::JSAB
{
	class TutorialMusicController;
	class PlayerPieces;
	class InGameTriangle;
}

namespace lu::JSAB::Tutorial
{
	class TutorialScene : public Scene
	{
	public:
		TutorialScene(){}
		virtual ~TutorialScene(){}

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		void OnActivate();
		

	private:
		TutorialMusicController* music;
		InGameTriangle* mTriangle;
		PlayerPieces* mOpening;
		GameObject* mPlayer;
		double mTime;
		bool mTriFlag;
	};
}

