#include "TutorialMusicController.h"
#include "LGameObject.h"
#include "LResources.h"
#include "LAudioSource.h"
#include "LTime.h"
#include "LFontWrapper.h"
#include "LInput.h"
namespace lu::JSAB
{
	TutorialMusicController::TutorialMusicController()
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
		mEndTime = mCheckPoints[10].second;
	}

	void TutorialMusicController::Initialize()
	{
		MusicController::Initialize();
		mAudioSource = Owner()->AddComponent<AudioSource>();
		mAudioSource->SetClip(Resources::Load<AudioClip>(L"TestSound", L"..\\..\\Assets\\AudioClips\\GameMusic\\mus_corrupted.wav"));
		mStartVolume = mAudioSource->GetVolume();
	}
	
	void TutorialMusicController::Update()
	{
		if (mbIsPlaying)
		{
			double time = mAudioSource->GetPosition();
			if (time < mEndTime)
			{
				if (time > mCheckPoints[mStageIdx].second)
				{
					if (mNextStageIdx > mStageIdx) mStageIdx = mNextStageIdx;
					mAudioSource->SetPosition(mCheckPoints[mStageIdx].first);
				}
			}
			else if (mAudioSource->GetVolume() > 0)
			{
				float fadeStep = mFadeTime / mFadeDuration;
				float vol = mStartVolume * (1.0f - fadeStep);
				
				mAudioSource->SetVolume(vol);
				mFadeTime += Time::DeltaTime();
			}
			else
			{
				mAudioSource->Stop();
			}
		}
		if (Input::GetKeyDown(eKeyCode::Q))
			PlayNextPart();
	}
	void TutorialMusicController::PlayNextPart()
	{
		if (mNextStageIdx < mCheckPoints.size() - 1)
			mNextStageIdx++;		
	}
}