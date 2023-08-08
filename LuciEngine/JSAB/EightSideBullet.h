#pragma once
#include "..\\Engine_SOURCE\\LGameObject.h"

namespace lu::JSAB
{
	class EightSideBullet : public GameObject
	{
	public:
		EightSideBullet();
		virtual ~EightSideBullet();

		virtual void Initialize() override;
	};
}

