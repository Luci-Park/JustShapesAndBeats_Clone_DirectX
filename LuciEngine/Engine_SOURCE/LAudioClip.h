#pragma once
#include "LResource.h"
#include "LFmod.h"

namespace lu
{
	class AudioClip : public Resource
	{
	public:
		AudioClip();
		~AudioClip();
		
		virtual HRESULT Load(const std::wstring& path) override;

		void Play();
		void Pause(bool pause);
		void Stop();
		void SetPosition(int position_ms);
		int GetPosition();
		void SetVolume(float volume);
		float GetVolume();
		void SetLoop(bool loop) { Loop = loop; }
	private:
		FMOD::Sound* mSound;
		FMOD::Channel* mChannel;
		bool Loop;
	};
}

