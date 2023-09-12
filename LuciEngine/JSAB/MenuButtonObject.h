#pragma once
#include "LGameObject.h"
namespace lu
{
	class Animator;
}
namespace lu::JSAB
{
	class MenuButtonObject : public GameObject
	{
	public:
		MenuButtonObject(eLayerType layer):GameObject(layer){}
		virtual ~MenuButtonObject(){}

		virtual void Initialize() override;
	private:
		Animator* mAnim;
	};
}

