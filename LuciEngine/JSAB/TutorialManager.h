#pragma once
#include "LScript.h"
namespace lu::JSAB
{
	class TutorialManager : public Script
	{
	public:
		TutorialManager();

		virtual void Initialize() override;
		virtual void Update() override;
	};
}

