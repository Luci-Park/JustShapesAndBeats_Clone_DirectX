#include "MusicController.h"
#include "LAudioSource.h"
#include "LGameObject.h"
#include "LTime.h"
namespace lu::JSAB
{
	MusicController* MusicController::Instance = nullptr;
	MusicController::MusicController()
		: mStageIdx(0)
		, mNextStageIdx(0)
		, mFadeDuration(2)
		, mFadeTime(0)
	{
	}
	void MusicController::Initialize()
	{
		mAudioSource = Owner()->AddComponent<AudioSource>();
	}
	void MusicController::Update()
	{
		if (mbIsPlaying)
		{
			double time = GetTime();
			if (time < mEndTime)
			{
				if (time > mCheckPoints[mStageIdx].second)
				{
					if (mNextStageIdx > mStageIdx) mStageIdx = mNextStageIdx;
					//checkpoint
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
	}
	void MusicController::Play()
	{
		mbIsPlaying = true;
		mAudioSource->SetPosition(0);
		mAudioSource->Play();
		Instance = this;
	}
	void MusicController::Stop()
	{
		mbIsPlaying = false;
		mAudioSource->Stop();
		Instance = nullptr;
	}
	double MusicController::GetTime()
	{
		return mAudioSource->GetPosition();
	}
}