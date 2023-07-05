#pragma once
#include "LGameObject.h"
namespace lu::JSAB::Menu
{
	class MenuButtonObject : public GameObject
	{
	public:
		MenuButtonObject(){}
		virtual ~MenuButtonObject(){}

		virtual void Initialize() override;
	};
}

