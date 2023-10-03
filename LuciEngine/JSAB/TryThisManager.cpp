#include "LCamera.h"
#include "TryThisManager.h"
#include "CameraScript.h"
#include "CheckPoint.h"


namespace lu::JSAB
{
	TryThisManager::TryThisManager()
	{
	}
	void TryThisManager::Initialize()
	{
		mMusic = Owner()->GetComponent<MusicController>();
		mCheckPoint = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<CheckPoint>();
		mCheckPoint->SetBackground(SceneManager::MainCamera()->Owner()->GetComponent<GameCamera>()->GetBackground());
		mCheckPoint->SetManager(this);

		mScope = object::Instantiate<GameObject>(eLayerType::Item)->AddComponent<TryThisScope>();
		mScope->SetTimeline(mMusic, 0, .850, 8.400 - .850);
	}
	void TryThisManager::Update()
	{
		double time = mMusic->GetTime();
		Scope(time);
		MusicManager::Update();
	}
	void TryThisManager::Play()
	{
		mbScopeFlag = 0;
		MusicManager::Play();
	}
	void TryThisManager::OnMusicEnd()
	{
		mMusic->Finish();
		mbFin = true;
	}
	void TryThisManager::Scope(double time)
	{
		static int beat[] = { 2.95, 3.425, 3.9, 5.55, 6.075, 6.6 };

		if (mbScopeFlag < 23 && time >= beat[mbScopeFlag])
		{
			mScope->Bump();
			mbScopeFlag++;
		}
	}
}