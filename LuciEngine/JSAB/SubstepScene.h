#pragma once
#include "LScene.h"
namespace lu::JSAB
{
	class SubstepScene : public Scene
	{
	public:
		SubstepScene();
		virtual ~SubstepScene();

		virtual void Initialize() override;
		virtual void Update() override;
	};
}

