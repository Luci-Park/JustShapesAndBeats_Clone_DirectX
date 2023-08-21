#include "LAudioSource.h"
#include "LTransform.h"
#include "LGameObject.h"
namespace lu
{
	AudioSource::AudioSource()
		: Component(eComponentType::AudioSource)
		, mAudioClip(nullptr)
		, is3D(true)
	{
	}

	AudioSource::~AudioSource()
	{
	}

	void AudioSource::Initialize()
	{
	}

	void AudioSource::Update()
	{
	}

	void AudioSource::LateUpdate()
	{
		if (is3D)
		{
			Transform* tr = Owner()->GetComponent<Transform>();
			Vector3 pos = tr->GetPosition();
			Vector3 foward = tr->Forward();

			mAudioClip->Set3DAttributes(pos, foward);
		}
	}

	void AudioSource::Render()
	{
	}

	void AudioSource::Play()
	{
		mAudioClip->Play();
	}

	void AudioSource::Play(bool loop)
	{
		mAudioClip->SetLoop(loop);
		mAudioClip->Play();
	}

	void AudioSource::PlayReversed()
	{
		mAudioClip->PlayReversed();
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
}