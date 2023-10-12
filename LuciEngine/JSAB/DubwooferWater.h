#pragma once
#include "LScript.h"
#include "DubwooferWaterBullet.h"
namespace lu::JSAB
{
	class DubwooferWater : public Script
	{
	public:
		struct Ripple
		{
			float origin;
			float startTime;
			float amplitude;
			float waveLength;
			float period;
		};
		DubwooferWater() {}
		virtual ~DubwooferWater() {}

		virtual void Initialize() override;
		virtual void Update() override;

		void OnImpact(int idx, Transform* target);
		void RippleTest(int idx);
	private:
		std::vector<DubwooferWaterBullet*> mWater;
		std::list<Ripple> mRipples;
		float mTime;
	};
}

