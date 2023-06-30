#pragma once
#include "LScene.h"

namespace lu::JSAB
{
	class TryThisScene : public Scene
	{
	public:
		TryThisScene();
		virtual ~TryThisScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}

