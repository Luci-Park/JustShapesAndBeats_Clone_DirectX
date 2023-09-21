#include "MusicController.h"
#include "LAudioSource.h"
#include "LGameObject.h"
#include "LTime.h"
#include "LText.h"
namespace lu::JSAB
{
	MusicController* MusicController::Instance = nullptr;
	MusicController::MusicController()
		: mStageIdx(0)
		, mNextStageIdx(0)
		, mFadeDuration(2)
		, mFadeTime(0)
		, mbIsFinishing(false)
	{
	}
	void MusicController::Initialize()
	{
		mAudioSource = Owner()->AddComponent<AudioSource>();
		mText = Owner()->AddComponent<Text>();
		mText->size = 60;
		mText->color = Color::yellow;
	}
	void MusicController::Update()
	{
		if (mbIsFinishing)
		{
			if (mAudioSource->GetVolume() > 0)
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
		mbIsFinishing = false;
	}
	void MusicController::Stop()
	{
		mbIsPlaying = false;
		mAudioSource->Stop();
		Instance = nullptr;
		mbIsFinishing = false;
	}
	double MusicController::GetTime()
	{
		return mAudioSource->GetPosition();
	}
	float MusicController::GetPercent()
	{
		return GetTime() / mCheckPoints[mStageIdx].second;
	}
}