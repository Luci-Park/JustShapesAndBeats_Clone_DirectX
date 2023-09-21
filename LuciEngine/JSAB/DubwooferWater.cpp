#include "DubwooferWater.h"
#include "LGameObject.h"
#include "LObject.h"
#include "LTime.h"
namespace lu::JSAB
{
	void DubwooferWater::Initialize()
	{
		Script::Initialize();

		int waternumber = 107;
		float xsize = 10;
		float offset = 2;
		float width = xsize + offset;
		float fullwidth = width * waternumber;
		float startx = -fullwidth * 0.5;
		for (int i = 0; i < waternumber; i++)
		{
			auto c = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<DubwooferWaterBullet>();
			mWater.push_back(c);
			c->mTransform->SetLocalPosition(startx + width * 0.5 + width * i, 0, 0);
		}
		mTime = 0;
	}
	void DubwooferWater::Update()
	{
		float minSize = 300;
		float amplitude = 30;
		float period = 2;

		mTime += Time::DeltaTime();
		for (int i = 0; i < mWater.size(); i++)
		{
			mWater[i]->SetY(minSize + sinf((mTime + i* 0.2) /period) * amplitude);
		}
	}
}