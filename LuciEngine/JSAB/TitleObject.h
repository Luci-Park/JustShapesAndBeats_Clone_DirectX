#pragma once
#include "LGameObject.h"
namespace lu::JSAB::Menu
{
	class TitleObject : public GameObject
	{
	public:
		TitleObject(eLayerType layer):GameObject(layer) {}
		virtual ~TitleObject() {}
		virtual void Initialize() override;
	};
}

