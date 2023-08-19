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
		void PlayReversed();
		void Pause(bool pause);
		void Stop();
		void SetPosition(int position_ms);
		void Set3DAttributes(const Vector3 pos, const Vector3 vel);
		void SetLoop(bool loop) { mbLoop = loop; }
	private:
		FMOD::Sound* mSound;
		FMOD::Channel* mChannel;
		float mMinDistance;
		float mMaxDistance;
		bool mbLoop;
	};
}

