#pragma once
#include "..\\Engine_SOURCE\\LScript.h"
namespace lu::JSAB
{
	class MusicManager : public Script
	{
	public:
		static MusicManager* Instance;
		MusicManager() {}
		virtual ~MusicManager(){}

		virtual void Play();
		virtual void OnMusicEnd() = 0;
		virtual void OnStageEnd();
	protected:
		std::wstring mNextScene;
	};
} 