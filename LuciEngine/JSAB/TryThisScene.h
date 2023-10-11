#pragma once
#include "..\Engine_SOURCE\LScene.h"
#include "BackgroundScript.h"
#include "TryThisManager.h"

namespace lu::JSAB
{
	class TryThisScene : public Scene
	{
	public:
		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		TryThisManager* mManager;
		BackgroundScript* mBackground;
		GameObject* mPlayer;
	};
}

