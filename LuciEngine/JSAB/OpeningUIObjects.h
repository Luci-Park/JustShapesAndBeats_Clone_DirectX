#pragma once
#include "LGameObject.h"
namespace lu
{
	class Animator;
}
namespace lu::JSAB::Title
{
	class ShapesObject : public GameObject
	{
	public:
		ShapesObject(eLayerType layer) : GameObject(layer){}
		virtual ~ShapesObject(){}
		virtual void Initialize() override;
	};

	class AndObject : public GameObject
	{
	public:
		AndObject(eLayerType layer) : GameObject(layer) {}
		virtual ~AndObject(){}
		virtual void Initialize() override;
	};

	class BeatsObject : public GameObject
	{
	public:
		BeatsObject(eLayerType layer) : GameObject(layer) {}
		virtual ~BeatsObject(){}
		virtual void Initialize() override;
	};

	class LightCircleObject : public GameObject
	{
	public:
		LightCircleObject(eLayerType layer) : GameObject(layer) {}
		virtual ~LightCircleObject(){}
		virtual void Initialize() override;
	};
}

