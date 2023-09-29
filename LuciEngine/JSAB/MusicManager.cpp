#include "MusicManager.h"
#include "LSceneManager.h"

namespace lu::JSAB
{
	MusicManager* MusicManager::Instance = nullptr;
	void MusicManager::Play()
	{
		Instance = this;
	}
	void MusicManager::OnStageEnd()
	{
		SceneManager::LoadScene(mNextScene);
		Instance = nullptr;
	}
}