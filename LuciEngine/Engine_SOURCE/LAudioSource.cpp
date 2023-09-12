#include "LAudioSource.h"
#include "LTransform.h"
#include "LGameObject.h"
namespace lu
{
	AudioSource::AudioSource()
		: Component(eComponentType::AudioSource)
		, mAudioClip(nullptr)
	{
	}

	AudioSource::~AudioSource()
	{
	}

	void AudioSource::Play()
	{
		if (mAudioClip == nullptr) return;
		mAudioClip->Play();
	}

	void AudioSource::Play(bool loop)
	{
		if (mAudioClip == nullptr) return;
		mAudioClip->SetLoop(loop);
		mAudioClip->Play();
	}

	void AudioSource::Pause()
	{
		mAudioClip->Pause(true);
	}

	void AudioSource::UnPause()
	{
		mAudioClip->Pause(false);
	}

	void AudioSource::Stop()
	{
		mAudioClip->Stop();
	}

	void AudioSource::SetLoop(bool loop)
	{
		mAudioClip->SetLoop(loop);
	}
	void AudioSource::SetPosition(double position_sec)
	{
		int position_ms = static_cast<int>(round(position_sec * 1000));
		mAudioClip->SetPosition(position_ms);
	}
	double AudioSource::GetPosition()
	{
		int milisec = mAudioClip->GetPosition();
		double position_seconds = static_cast<double>(milisec) / 1000.0;
		return position_seconds;
	}
	void AudioSource::SetVolume(float volume)
	{
		mAudioClip->SetVolume(volume);
	}
	float AudioSource::GetVolume()
	{
		return mAudioClip->GetVolume();
	}
	bool AudioSource::IsPlaying()
	{
		return(mAudioClip != nullptr && mAudioClip->IsPlaying());
	}
	bool AudioSource::IsPlaying(std::shared_ptr<AudioClip> clip)
	{
		return mAudioClip == clip && IsPlaying();
	}
}