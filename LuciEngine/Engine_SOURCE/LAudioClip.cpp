#include "LAudioClip.h"

namespace lu
{
	AudioClip::AudioClip()
		:Resource(enums::eResourceType::AudioClip)
		, mSound(nullptr)
		, mChannel(nullptr)
		, mMinDistance(1.0f)
		, mMaxDistance(1000.0f)
		, mbLoop(false)
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

		mSound->set3DMinMaxDistance(mMinDistance, mMaxDistance);
		Fmod::Play(mSound, &mChannel);
		mChannel->setPaused(true);
		return S_OK;
	}
	void AudioClip::Play()
	{
		if (mbLoop)
			mSound->setMode(FMOD_LOOP_NORMAL);
		else
			mSound->setMode(FMOD_LOOP_OFF);

		mChannel->setPaused(false);
	}

	void AudioClip::PlayReversed()
	{
		mChannel->setPaused(true);
		mChannel->setFrequency(2.0f);
		mChannel->setPaused(false);
	}

	void AudioClip::Pause(bool pause)
	{
		mChannel->setPaused(pause);
	}

	void AudioClip::Stop()
	{
		mChannel->stop();
	}
	void AudioClip::SetPosition(int position_ms)
	{
		mChannel->setPaused(true);
		mChannel->setPosition(position_ms, FMOD_TIMEUNIT_MS);
		mChannel->setPaused(false); 
	}
	void AudioClip::Set3DAttributes(const Vector3 pos, const Vector3 vel)
	{
		FMOD_VECTOR fmodPos(pos.x, pos.y, pos.z);
		FMOD_VECTOR fmodVel(vel.x, vel.y, vel.z);

		mChannel->set3DAttributes(&fmodPos, &fmodVel);
	}
}