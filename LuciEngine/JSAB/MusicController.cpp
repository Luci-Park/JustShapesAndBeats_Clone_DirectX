#include "MusicController.h"
#include "LResources.h"
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
	void MusicController::SetClip(std::wstring clip)
	{
		mAudioSource->SetClip(Resources::Find<AudioClip>(clip));
		mStartVolume = mAudioSource->GetVolume();
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
		if (mbIsPlaying)
		{
			if (GetTime() >= mCheckPoints[mStageIdx].second)
				mStageIdx++;
			mText->text = mAudioSource->GetPosition();
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