#pragma once
#include "LGameObject.h"
namespace lu::JSAB::Menu
{
	class MenuButtonObject : public GameObject
	{
	public:
		MenuButtonObject(eLayerType layer):GameObject(layer){}
		virtual ~MenuButtonObject(){}

		virtual void Initialize() override;
	};
}

