#pragma once
#include "..\Engine_SOURCE\LScene.h"
#include "BackgroundScript.h"
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

	private:
		BackgroundScript* mbgs;
	};
}

