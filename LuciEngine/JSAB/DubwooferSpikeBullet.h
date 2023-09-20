#pragma once
#include "LScript.h"

namespace lu
{
	class Animator;
	class Rigidbody;
	class ParticleSystem;
	class MeshRenderer;
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

		void DeActivate() {}
	private:
	};
}

