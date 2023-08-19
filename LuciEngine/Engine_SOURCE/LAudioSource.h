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

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void Play();
		void Play(bool loop);
		void PlayReversed();
		void Pause();
		void UnPause();
		void Stop();
		void SetLoop(bool loop);
		void SetPosition(double position_sec);
		void SetClip(std::shared_ptr<AudioClip> clip) { mAudioClip = clip; }
		std::shared_ptr<AudioClip> GetClip() { return mAudioClip; }
		void Is3D(bool is3d) { this->is3D = is3D; }
	private:
		bool is3D;
		std::shared_ptr<AudioClip> mAudioClip;
	};
}

