#pragma once
#include "..\\Engine_SOURCE\\LGameObject.h"

namespace lu::JSAB
{
	class PlayerObject : public GameObject
	{
	public:
		PlayerObject();
		virtual ~PlayerObject();

		virtual void Initialize() override;
	};
}

