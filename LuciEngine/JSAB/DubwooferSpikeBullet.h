#pragma once
#include "LScript.h"

namespace lu
{
	class Animator;
	class Rigidbody;
	class Collider2D;
}

namespace lu::JSAB
{
	class DubwooferSpikeBullet : public Script
	{
	public:
		DubwooferSpikeBullet() {}
		virtual ~DubwooferSpikeBullet() {}

		virtual void Initialize() override;
		//virtual void Update() override;
		void Reset();
		void Activate();
	private:
		Animator* mSpikeAnim;
		Rigidbody* mRb;

	};
}

