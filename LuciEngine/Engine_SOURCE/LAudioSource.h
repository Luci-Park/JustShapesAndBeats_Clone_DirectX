#pragma once
#include "LComponent.h"
#include "LAudioClip.h"

namespace lu
{
	class AudioSource : public Component
	{
	public:
		AudioSource();
		~AudioSource();

		void Play();
		void Play(bool loop);
		void Pause();
		void UnPause();
		void Stop();
		void SetLoop(bool loop);
		void SetPosition(double position_sec);
		double GetPosition();
		void SetVolume(float volume);
		float GetVolume();
		void SetClip(std::shared_ptr<AudioClip> clip) { mAudioClip = clip; }
		std::shared_ptr<AudioClip> GetClip() { return mAudioClip; }
	private:
		std::shared_ptr<AudioClip> mAudioClip;
	};
}

