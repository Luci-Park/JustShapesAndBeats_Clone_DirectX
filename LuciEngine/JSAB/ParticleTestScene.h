#pragma once
#include "..\Engine_SOURCE\LScene.h"
namespace lu::JSAB
{
	class ParticleTestScene : public Scene
	{
	public:
		ParticleTestScene();
		virtual ~ParticleTestScene();

		virtual void Initialize() override;

	};
}
