#pragma once
#include "LScene.h"

namespace lu::JSAB
{
	class AnnhilateScene : public Scene
	{
	public:
		AnnhilateScene();
		virtual ~AnnhilateScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}
