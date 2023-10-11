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
		mbWaitForLoadScene = false;
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
				mbFin = false;
			}
		}
		else if (mbWaitForLoadScene)
		{
			mLevelEndCounter += Time::DeltaTime();
			if(mLevelEndCounter >= 3.5)
			{
				SceneManager::LoadScene(mNextScene);
				Instance = nullptr;
				mbWaitForLoadScene = false;
				mLevelEndCounter = 0;
			}

		}
	}
	void MusicManager::Play()
	{
		Instance = this;
		mTriangleAppearTime = 3.f;
		mLevelEndCounter = 0;
		mbFin = false;
		mLevelTriangle->Owner()->SetActive(false);
		mMusic->Play();
	}
	void MusicManager::OnLevelEnd()
	{
		mbWaitForLoadScene = true;
		mLevelEndCounter = 0;
	}
}