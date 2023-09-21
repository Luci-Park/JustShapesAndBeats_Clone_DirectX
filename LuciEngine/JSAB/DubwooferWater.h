#pragma once
#include "LScript.h"
#include "DubwooferWaterBullet.h"
namespace lu::JSAB
{
	class DubwooferWater : public Script
	{
	public:
		DubwooferWater(){}
		virtual ~DubwooferWater(){}

		virtual void Initialize() override;
		virtual void Update() override;

	private:
		std::vector<DubwooferWaterBullet*> mWater;
		float mTime;
	};
}

