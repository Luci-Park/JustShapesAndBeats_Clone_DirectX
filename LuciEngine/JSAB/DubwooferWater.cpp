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
		}
		mTime = 0;

		Ripple ripple;
		ripple.origin = Vector3::Zero;
		ripple.startTime = 0;
		ripple.waveLength = 1;
		ripple.amplitude = 60;
		mRipples.push_back(ripple);
	}
	void DubwooferWater::Update()
	{
		float elevation = 300;
		float amplitude = 50;
		float waveLength = 3;

		mTime += Time::DeltaTime();
		for (int i = 0; i < mWater.size(); i++)
		{
			float idleWaveHeight = sinf((mTime + i * 0.2) / waveLength) * amplitude;
			float rippleHeight = 0;
			for (auto it = mRipples.begin(); it != mRipples.end();)
			{ 
				Ripple ripple = *it;
				float distanceToRipple = abs(mWater[i]->mTransform->GetPosition().x - ripple.origin.x);

				// Calculate the phase of the ripple based on time and distance
				float phase = (mTime - ripple.startTime - i * 1/*ripple.speed*/) * (2 * PI / ripple.waveLength);

				// Calculate the vertical displacement for the dynamic ripple using a sine wave equation
				rippleHeight += ripple.amplitude * sinf(phase);

				it++;
			}

			mWater[i]->SetY(idleWaveHeight + rippleHeight + elevation);
		}
	}
	void DubwooferWater::OnImpact(int idx, Transform* target)
	{
	}
}