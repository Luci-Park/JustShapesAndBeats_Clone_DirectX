#pragma once
#include "LGameObject.h"
namespace lu::JSAB
{
	class BackgroundScript;
	class BackgroundObject : public GameObject
	{
	public:
		BackgroundObject();
		virtual ~BackgroundObject();

		virtual void Initialize() override;

	private:
		BackgroundScript* mBackground;
	};
}

