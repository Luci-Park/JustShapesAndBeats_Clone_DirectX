#include "LTutorialMusicController.h"
#include "LGameObject.h"
#include "LResources.h"
#include "LAudioSource.h"
#include "LTime.h"
namespace lu::JSAB
{
	TutorialMusicController::TutorialMusicController()
		: mEndTime(200)
		, mTime(0)
		, mIdx(0)
	{
        mCheckPoints = {
            std::make_pair(0.763, 7.691),
            std::make_pair(7.691, 14.619),
            std::make_pair(14.646, 21.547),
            std::make_pair(28.475, 35.403),
            std::make_pair(35.403, 42.331),
            std::make_pair(42.331, 49.259),
            std::make_pair(56.187, 63.115),
            std::make_pair(70.043, 76.971),
            std::make_pair(76.971, 83.899),
            std::make_pair(111.611, 125.467),
            std::make_pair(125.467, 160.107)
        };	
	}

	void TutorialMusicController::Initialize()
	{
		mAudioSource = Owner()->AddComponent<AudioSource>();
		mAudioSource->SetClip(Resources::Load<AudioClip>(L"TestSound", L"..\\..\\Assets\\AudioClips\\GameMusic\\mus_corrupted.wav"));
	}
	
	void TutorialMusicController::Update()
	{
		if (mbIsPlaying)
		{
			mTime += Time::DeltaTime();
			if (mTime > mCheckPoints[mIdx].second)
			{
				if (mIdx + 1 < mCheckPoints.size())
				{
					mAudioSource->SetPosition(mCheckPoints[++mIdx].first);
					mTime = mCheckPoints[mIdx].first;
				}
				else
				{
					mTime = 0;
					mAudioSource->SetPosition(0);
				}
			}
		}
	}
	void TutorialMusicController::Play()
	{
		mbIsPlaying = true;
		mAudioSource->Play();
	}
}