#include "DubwooferDropSpawner.h"
#include "LApplication.h"
#include "LInput.h"

extern lu::Application application;
namespace lu::JSAB
{
	DubwooferDropSpawner::DubwooferDropSpawner()
		: mDrops(10)
	{
		float y = application.GetHeight() * 0.5;
		for (float i = application.GetWidth() * -0.5 + 50; i <= application.GetWidth() * 0.5 - 50; i += 20)
		{
			mSpawnPos.push_back({ i, y, 0 });
		}
	}
	void DubwooferDropSpawner::OnActivate()
	{
		auto a = mDrops.GetNext();
		a->mTransform->SetPosition(GetRandomSpawn());
		a->Activate();
	}
	Vector3 DubwooferDropSpawner::GetRandomSpawn()
	{
		int idx;
		do
		{
			idx = IntRandom(0, mSpawnPos.size() - 1);
		} while (idx == mPrevSpawn);
		mPrevSpawn = idx;

		return mSpawnPos[idx];
	}
}