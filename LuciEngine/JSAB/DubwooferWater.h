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
			Vector3 origin;
			float startTime;
			float duration;
			float waveLength;
			float amplitude;
		};
		DubwooferWater(){}
		virtual ~DubwooferWater(){}

		virtual void Initialize() override;
		virtual void Update() override;

		void OnImpact(int idx, Transform* target);
	private:
		std::vector<DubwooferWaterBullet*> mWater;
		std::list<Ripple> mRipples;
		float mTime;
	};
}

