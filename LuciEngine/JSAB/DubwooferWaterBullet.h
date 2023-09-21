#pragma once
#include "LScript.h"
namespace lu
{
	class Animator;
	class ParticleSystem;
	class MeshRenderer;
}
namespace lu::JSAB
{
	class DubwooferWater;
	class DubwooferWaterBullet : public Script
	{
	public:
		DubwooferWaterBullet(){}
		virtual ~DubwooferWaterBullet(){}

		virtual void Initialize() override;
		virtual void OnCollisionEnter(Collider2D* other) override;

		void SetY(float y);
		void SetParent(DubwooferWater* p) { mParent = p; }
	private:
		DubwooferWater* mParent;

		Animator* mAnim;
		ParticleSystem* mPs;
		MeshRenderer* mMr;
		Collider2D* mCol;
		bool mbInAction;
		
	};
}

