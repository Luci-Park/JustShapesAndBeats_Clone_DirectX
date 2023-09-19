#pragma once
#include "..\Engine_SOURCE\LScene.h"

namespace lu::JSAB
{
	class DubwooferSubstepScene : public Scene
	{ 
	public:
		virtual void Initialize() override;
		virtual void Update() override;

	};
}

