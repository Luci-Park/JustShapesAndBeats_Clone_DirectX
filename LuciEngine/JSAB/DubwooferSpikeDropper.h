#pragma once
#include "LScript.h"
#include "DubwooferSpikeBullet.h"
namespace lu::JSAB
{
	class DubwooferSpikeDropper : public Script
	{
	public:
		DubwooferSpikeDropper();
		virtual ~DubwooferSpikeDropper() {}

		void Initialize();
	private:
		std::vector<DubwooferSpikeBullet*> mSpikes;
	};
}

