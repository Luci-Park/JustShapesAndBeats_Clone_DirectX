#pragma once
#include "..\Engine_SOURCE\LScene.h"
namespace lu::JSAB
{
	class TestScene : public Scene
	{
	public:
		TestScene();
		virtual ~TestScene();

		virtual void Initialize() override;

	};
}
