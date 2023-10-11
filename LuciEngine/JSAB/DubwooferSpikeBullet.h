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
		void Reset();
		void Activate();
		void Shake();
	private:
		Animator* mSpikeAnim;
		Rigidbody* mRb;
		GameObject* mSpike;

	};
}

