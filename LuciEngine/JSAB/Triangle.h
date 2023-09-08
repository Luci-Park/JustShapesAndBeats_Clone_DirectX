#pragma once
#include "LScript.h"
namespace lu::JSAB
{
	class Triangle : public Script
	{
	public:
		Triangle() {}
		virtual ~Triangle() {}
		virtual void OnCollisionEnter(Collider2D* other) override;
	};
}

