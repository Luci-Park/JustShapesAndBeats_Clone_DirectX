#pragma once

#include "..\Engine_SOURCE\LScene.h"
namespace lu::JSAB::MainMenu
{
	class MenuScene : public Scene
	{
	public:
		MenuScene();
		virtual ~MenuScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}

