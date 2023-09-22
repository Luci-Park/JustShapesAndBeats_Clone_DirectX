#include "DubwooferSpikeDropper.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"
#include "LObject.h"
#include "LApplication.h"
#include "LInput.h"
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
		float x = 100;
		float offset = -15;
		float width = x + offset;
		float fullWidth = width * 16;
		float startx = -fullWidth * 0.5;
		for (int i = 0; i < 16; i++)
		{
			auto c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<DubwooferSpikeBullet>();
			mSpikes.push_back(c);
			c->mTransform->SetLocalPosition(startx + width *0.5 + width * i, 0, -0.01 * i);
		}
		mSpikes[7]->Owner()->AddComponent<gui::TransformWidget>();
	}
	void DubwooferSpikeDropper::Update()
	{
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			mSpikes[7]->Activate();
		}
	}
}