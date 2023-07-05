#pragma once
#include "LGameObject.h"
namespace lu::JSAB::Menu
{
	class TitleObject : public GameObject
	{
	public:
		TitleObject() {}
		virtual ~TitleObject() {}
		virtual void Initialize() override;
	};
}

