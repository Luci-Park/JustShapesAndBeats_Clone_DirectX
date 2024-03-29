#include "DubwooferWater.h"
#include "LGameObject.h"
#include "LObject.h"
#include "LTime.h"
namespace lu::JSAB
{
	void DubwooferWater::Initialize()
	{
		Script::Initialize();
		Owner()->SetName(L"WaterBody");
		int waternumber = 107;
		float xsize = 10;
		float offset = 2;
		float width = xsize + offset;
		float fullwidth = width * waternumber;
		float startx = -fullwidth * 0.5;
		for (int i = 0; i < waternumber; i++)
		{
			auto c = object::Instantiate<GameObject>(mTransform, eLayerType::BulletInteractor)->AddComponent<DubwooferWaterBullet>();
			mWater.push_back(c);
			c->mTransform->SetLocalPosition(startx + width * 0.5 + width * i, 0, 0);
			c->SetWaterBody(this, i);
			c->Owner()->SetName(L"Water " + std::to_wstring(i));
		}
		mTime = 0;

	}
	void DubwooferWater::Update()
	{
		float elevation = 300;
		float amplitude = 50;
		float waveLength = 3;

		mTime += Time::DeltaTime();

		for (int i = 0; i < mWater.size(); i++)
		{
			float idleWaveHeight = cosf((mTime + i * 0.2) / waveLength) * amplitude;
			float rippleHeight = 0;
			for (auto it = mRipples.begin(); it != mRipples.end();)
			{
				Ripple ripple = *it;
				float pos = ripple.origin + ripple.waveLength / ripple.period * mTime;
				float distanceFromImpact = fabs(mWater[i]->mTransform->GetPosition().x - ripple.origin);
				if (distanceFromImpact <= pos)
				{
					float height = ripple.amplitude * cosf(distanceFromImpact - ripple.waveLength / ripple.period * mTime);
					if (height > 0)
						rippleHeight += height;
				}
				it++;
			}

			mWater[i]->SetY(idleWaveHeight + rippleHeight + elevation);
		}
	}
	void DubwooferWater::OnImpact(int idx, Transform* target)
	{
	}
	void DubwooferWater::RippleTest(int idx)
	{
		if (idx == 0)
		{
			Ripple ripple;
			ripple.origin = 0;
			ripple.startTime = mTime;
			ripple.waveLength = 500;
			ripple.amplitude = 200;
			ripple.period = 3;
			mRipples.push_back(ripple);
		}
	}
}