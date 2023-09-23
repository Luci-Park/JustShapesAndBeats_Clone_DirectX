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
		void SetWaterBody(DubwooferWater* p, int idx) { mBody = p; mIdx = idx; }

	private:
		DubwooferWater* mBody;

		Animator* mAnim;
		ParticleSystem* mPs;
		MeshRenderer* mMr;
		Collider2D* mCol;
		bool mbInAction;
		int mIdx;
		
	};
}

