#pragma once
#include "LGameObject.h"

namespace lu::JSAB
{
	class Bullet : public GameObject
	{
	public:
		virtual void Preperation() = 0;
		virtual void Attack() = 0;
		virtual void Disappear() = 0;
	};
}

