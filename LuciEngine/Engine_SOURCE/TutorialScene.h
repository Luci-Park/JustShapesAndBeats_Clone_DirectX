#pragma once
#include "LScene.h"

namespace lu::JSAB
{
	class TutorialScene : public Scene
	{
	public:
		TutorialScene();
		virtual ~TutorialScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}

