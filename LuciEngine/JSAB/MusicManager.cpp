#include "MusicManager.h"
#include "LSceneManager.h"
#include "LTime.h"
#include "LObject.h"
#include "TrianglePrefab.h"
namespace lu::JSAB
{
	MusicManager* MusicManager::Instance = nullptr;
	MusicManager::MusicManager()
	{
		mLevelTriangle = object::Instantiate<TrianglePrefab>(eLayerType::Item)->GetComponent<InGameTriangle>();
		mLevelTriangle->Owner()->SetActive(false);
		mbFin = false;
	}
	void MusicManager::Update()
	{
		if(mbFin)
		{ 
			mLevelEndCounter += Time::DeltaTime();
			if (mLevelEndCounter >= mTriangleAppearTime && !mLevelTriangle->IsActive())
			{
				mLevelTriangle->SetStrategy(TriangleStrategy::eTriangleStrategyType::LevelFinish);
				mLevelTriangle->Appear();
			}
		}
	}
	void MusicManager::Play()
	{
		Instance = this;
		mTriangleAppearTime = 10.f;
		mLevelEndCounter = 0;
	}
	void MusicManager::OnLevelEnd()
	{
		SceneManager::LoadScene(mNextScene);
		Instance = nullptr;
	}
}