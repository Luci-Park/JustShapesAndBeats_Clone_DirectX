#include "DubwooferManager.h"
#include "DubwooferDropSpawner.h"
#include "DubwooferSpikeDropper.h"
#include "DubwooferBeamBullet.h"
#include "TutorialBeam.h"
#include "MusicController.h"
#include "LObject.h"

namespace lu::JSAB
{
	DubwooferManager::DubwooferManager()
		: mThickBeams(4)
		, mThinBeams(30)
	{
	}
	void DubwooferManager::Initialize()
	{
		mDrops = object::Instantiate<GameObject>(eLayerType::System)->AddComponent<DubwooferDropSpawner>();
		//mSpikes = object::Instantiate<GameObject>(eLayerType::System)->AddComponent<DubwooferSpikeDropper>();
		mMusic = Owner()->GetComponent<MusicController>();
	}
	void DubwooferManager::Update()
	{
		double time = mMusic->GetTime();
		Drops(time);
		//Spikes(time);
	}
	void DubwooferManager::Drops(double time)
	{
		static double beat[] = { 1, 1.25, 1.65, 2.75, 3, 3.4, 4.4, 4.65, 5.05, 6, 6.25, 6.55, 6.675, 6.8, 6.9, 7.05, 7.2, 7.7
			, 7.95, 8.35, 9.45, 9.7, 10.1, 11.1, 11.35, 11.75, 12.7, 12.95, 13.5, 13.65, 13.75, 13.8, 13.85, 13.95, 14
			, 14.15, 14.3,14.65, 14.8, 15.05, 15.35, 15.6, 15.9, 16.15, 16.45, 16.8, 17, 17.15, 17.25, 17.55, 17.85, 18.1
			, 18.5, 18.8, 18.9, 19.25, 19.5, 19.75, 20.05, 20.45, 20.55, 21, 21.3, 21.4, 21.7, 22, 22.25, 22.55, 22.8
			, 23.1, 23.35, 23.6, 23.75, 23.9, 24.15, 24.45, 24.7, 25.15, 25.4, 25.55, 25.85, 26.1, 26.4, 26.7, 27.05, 27.15, 27.2 };
		static int idx = 0;
		while (idx < 88 && time >= beat[idx])
		{
			mDrops->Activate();
			idx++;
		}
	}
	void DubwooferManager::Spikes(double time)
	{
	}
}