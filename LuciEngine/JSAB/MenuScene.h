#pragma once
#include "LScene.h"

namespace lu::JSAB
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

