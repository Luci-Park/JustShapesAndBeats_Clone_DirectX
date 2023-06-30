#pragma once
#include "LScene.h"

namespace lu::JSAB
{
	class DubwooferScene : public Scene
	{
	public:
		DubwooferScene();
		virtual ~DubwooferScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}

