#pragma once
#include "LGameObject.h"

namespace lu::JSAB
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

	class BeatsObjects : public GameObject
	{
	public:
		BeatsObjects(){}
		virtual ~BeatsObjects(){}
		virtual void Initialize() override;
	};
}

