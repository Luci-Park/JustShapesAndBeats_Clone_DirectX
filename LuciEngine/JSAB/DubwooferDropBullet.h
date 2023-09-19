#pragma once
#include "LScript.h"
namespace lu
{
	class Animator;
	class Rigidbody;
}

namespace lu::JSAB
{
	class DubwooferDropBullet : public Script
	{
	public:
		DubwooferDropBullet();
		~DubwooferDropBullet(){}

		virtual void Initialize();
		virtual void Update();
	private:
		Animator* mAnim;
		bool mbFall;
	};
}

