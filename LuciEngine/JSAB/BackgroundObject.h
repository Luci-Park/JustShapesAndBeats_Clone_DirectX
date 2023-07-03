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

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		BackgroundScript* mBackground;
	};
}

