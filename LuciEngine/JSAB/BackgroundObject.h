#pragma once
#include "LGameObject.h"
#include "BackgroundScript.h"
namespace lu::JSAB
{
	class BackgroundScript;
	class BackgroundObject : public GameObject
	{
	public:
		BackgroundObject(eLayerType layer);
		virtual ~BackgroundObject();

		virtual void Initialize() override;
	};
}

