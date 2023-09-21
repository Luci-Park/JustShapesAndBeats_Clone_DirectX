#pragma once
#include "LScript.h"
namespace lu
{
	class Animator;
	class ParticleSystem;
	class MeshRenderer;
	class Collider2D;
}
namespace lu::JSAB
{
	class DubwooferWaterBullet : public Script
	{
	public:
		DubwooferWaterBullet(){}
		virtual ~DubwooferWaterBullet(){}

		virtual void Initialize() override;
		void SetY(float y);
	
	private:
		Animator* mAnim;
		ParticleSystem* mPs;
		MeshRenderer* mMr;
		Collider2D* mCol;
	};
}

