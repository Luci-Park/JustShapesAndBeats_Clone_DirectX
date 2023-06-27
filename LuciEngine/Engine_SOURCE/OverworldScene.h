#pragma once
#include "LScene.h"

namespace lu::JSAB
{
	class OverworldScene : public Scene
	{
	public:
		OverworldScene();
		virtual ~OverworldScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}

