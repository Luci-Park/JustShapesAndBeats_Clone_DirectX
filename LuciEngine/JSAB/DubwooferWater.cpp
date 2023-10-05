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
		mTransform->SetPosition(0, -360, -0.1);
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
				float pos = ripple.origin.x + ripple.waveLength / ripple.period * mTime * 0.5;
				float distanceToRipple = abs(mWater[i]->mTransform->GetPosition().x - ripple.origin.x) * 2;
				if(distanceToRipple <= pos)
					rippleHeight += ripple.amplitude * cosf(distanceToRipple - ripple.waveLength / ripple.period * mTime);
				it++;
			}

			mWater[i]->SetY(idleWaveHeight + rippleHeight + elevation);
		}

		for (auto it = mRipples.begin(); it != mRipples.end();)
		{
			//(*it).waveLength += -(*it).waveDamp * (*it).waveLength* Time::DeltaTime();
			(*it).amplitude += -(*it).ampDamp * Time::DeltaTime();

			if ((*it).waveLength <= 0 || (*it).amplitude <= 0)
				it = mRipples.erase(it);
			else
				it++;
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
			ripple.origin = Vector3::Zero;
			ripple.startTime = 0;
			ripple.waveLength = 10;//0부터 0까지
			ripple.amplitude = 10;
			ripple.period = 0.25;//총시간
			ripple.waveDamp = 0.2;
			ripple.ampDamp = 0.3;
			mRipples.push_back(ripple);
		}
	}
}