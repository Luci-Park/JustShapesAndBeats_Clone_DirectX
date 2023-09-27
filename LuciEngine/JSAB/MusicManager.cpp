#include "MusicManager.h"
#include "LSceneManager.h"

namespace lu::JSAB
{
	void MusicManager::OnStageEnd()
	{
		SceneManager::LoadScene(mNextScene);
	}
}