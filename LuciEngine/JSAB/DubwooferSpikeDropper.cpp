#include "DubwooferSpikeDropper.h"
#include "..\\Editor_SOURCE\\TransformWidget.h"
#include "LObject.h"
#include "LApplication.h"
#include "LInput.h"
extern lu::Application application;

namespace lu::JSAB
{
	void DubwooferSpikeDropper::DropSpike()
	{
		int idx;
		do
		{
			idx = IntRandom(1, mSpikes.size() - 2);
		} while (idx == prevIdx);
		prevIdx = idx;
		for (int i = 0; i < mSpikes.size(); i++)
		{
			if (i == idx)
				mSpikes[i]->Activate();
			else
				mSpikes[i]->Shake();
		}
	}
	void DubwooferSpikeDropper::BulletSetUp()
	{
		mWaitPos = { 0, 420, 0 }; 
		mActivePos = { 0, 312.1346, 0 };

		mTransform->SetPosition(mWaitPos);
		float x = 100;
		float offset = -15;
		float width = x + offset;
		float fullWidth = width * 16;
		float startx = -fullWidth * 0.5;
		for (int i = 0; i < 16; i++)
		{
			auto c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<DubwooferSpikeBullet>();
			mSpikes.push_back(c);
			c->mTransform->SetLocalPosition(startx + width * 0.5 + width * i, 0, 0.01 * i);
		}
	}
	void DubwooferSpikeDropper::OnWarning()
	{
		mTransform->SetPosition(mWaitPos);
	}
	void DubwooferSpikeDropper::WhileWarning(double time)
	{
		Vector3 pos = Vector3::Lerp(mWaitPos, mActivePos, mWarningProcess);
		mTransform->SetPosition(pos);
	}

	void DubwooferSpikeDropper::OnActivate()
	{
		mTransform->SetPosition(mActivePos);
	}

	void DubwooferSpikeDropper::WhileOutro(double time)
	{
		float duration = 0.5;
		Vector3 pos = Vector3::Lerp( mActivePos, mWaitPos, mOutroProcess/duration);
		mTransform->SetPosition(pos);
		if (pos == mWaitPos)
			DeActivate();
	}

}