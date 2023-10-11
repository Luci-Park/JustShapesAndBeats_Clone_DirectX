#pragma once
#include "..\Engine_SOURCE\LScene.h"
#include "DubwooferManager.h"
#include "BackgroundScript.h"
namespace lu::JSAB
{
	class DubwooferSubstepScene : public Scene
	{ 
	public:
		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		DubwooferManager* mManager;
		BackgroundScript* mBackground;
		GameObject* mPlayer;
	};
}

