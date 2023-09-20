#include "DubwooferSpikeDropper.h"
#include "LObject.h"
#include "LApplication.h"

extern lu::Application application;

namespace lu::JSAB
{
	DubwooferSpikeDropper::DubwooferSpikeDropper()
	{
	}
	void DubwooferSpikeDropper::Initialize()
	{
		Script::Initialize();
		mTransform->SetPosition(0, 312.1346, 0);
		float width = 85;
		float fullWidth = width * 16;
		float startx = -fullWidth * 0.5;
		for (int i = 0; i < 16; i++)
		{
			auto c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<DubwooferSpikeBullet>();
			mSpikes.push_back(c);
			c->mTransform->SetLocalPosition(startx + width *0.5 + width * i, 0, -0.01 * i);
		}
	}
}