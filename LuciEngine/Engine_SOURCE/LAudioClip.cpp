#include "LAudioClip.h"

namespace lu
{
	AudioClip::AudioClip()
		:Resource(enums::eResourceType::AudioClip)
		, mSound(nullptr)
		, mChannel(nullptr)
		, Loop(false)
	{
	}
	AudioClip::~AudioClip()
	{
	}
	HRESULT AudioClip::Load(const std::wstring& path)
	{
		std::string cPath(path.begin(), path.end());
		if (!Fmod::CreateSound(cPath, &mSound))
			return S_FALSE;
		return S_OK;
	}
	void AudioClip::Play()
	{
		if (Loop)
			mSound->setMode(FMOD_LOOP_NORMAL);
		else
			mSound->setMode(FMOD_LOOP_OFF);
		Fmod::Play(mSound, &mChannel);
	}

	void AudioClip::Pause(bool pause)
	{
		mChannel->setPaused(pause);
	}

	void AudioClip::Stop()
	{
		mChannel->stop();
	}
	bool AudioClip::IsPlaying()
	{
		bool playing;
		mChannel->isPlaying(&playing);
		return playing;
	}
	void AudioClip::SetPosition(int position_ms)
	{
		if(mChannel != nullptr)
			mChannel->setPosition(position_ms, FMOD_TIMEUNIT_MS);
	}
	int AudioClip::GetPosition()
	{
		UINT ms;
		mChannel->getPosition(&ms, FMOD_TIMEUNIT_MS);
		return ms;
	}
	void AudioClip::SetVolume(float volume)
	{
		mChannel->setVolume(volume);
	}
	float AudioClip::GetVolume()
	{
		float v;
		mChannel->getVolume(&v);
		return v;
	}
}