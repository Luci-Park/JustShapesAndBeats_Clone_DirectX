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

	class DubwooferSpikeSingleWave : public Script
	{
	public:
		DubwooferSpikeSingleWave() {}
		virtual ~DubwooferSpikeSingleWave(){}

		virtual void Initialize() override;
		virtual void Update() override;
		void Activate();
	private:
		bool mbWave;
		double mTime;
		double mDuration;
	};

	class DubwooferSpikeWave : public Script
	{
	public:
		DubwooferSpikeWave() {}
		virtual ~DubwooferSpikeWave() {}

		virtual void Initialize() override;
		void Activate(Vector3 pos);
	private:
		DubwooferSpikeSingleWave* mWaves[5];
		Animator* mAnim;
	};

}

