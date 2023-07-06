#pragma once
#include "..\Engine_SOURCE\LScene.h"


namespace lu::JSAB::Tutorial
{
	class TutorialScene : public Scene
	{
	public:
		TutorialScene(){}
		virtual ~TutorialScene(){}

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}

