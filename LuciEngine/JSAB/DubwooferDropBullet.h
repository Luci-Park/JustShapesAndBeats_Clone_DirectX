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
	class DubwooferDropBullet : public Script
	{
	public:
		DubwooferDropBullet();
		~DubwooferDropBullet(){}

		virtual void Initialize();
		virtual void Update();

		void Activate();
		void DeActivate();
	private:
		Animator* mAnim;
		Rigidbody* mRb;
		ParticleSystem* mParticle;
		MeshRenderer* mMr;
		Collider2D* mCol;
	};
}

