#pragma once
#include "LGameObject.h"

namespace lu::JSAB::Title
{
	class ShapesObject : public GameObject
	{
	public:
		ShapesObject(){}
		virtual ~ShapesObject(){}
		virtual void Initialize() override;
	};

	class AndObject : public GameObject
	{
	public:
		AndObject(){}
		virtual ~AndObject(){}
		virtual void Initialize() override;
	};

	class BeatsObject : public GameObject
	{
	public:
		BeatsObject(){}
		virtual ~BeatsObject(){}
		virtual void Initialize() override;
	};

	class LightCircleObject : public GameObject
	{
	public:
		LightCircleObject(){}
		virtual ~LightCircleObject(){}
		virtual void Initialize() override;
	};
}

