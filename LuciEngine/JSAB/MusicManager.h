#pragma once
#include "LScript.h"
namespace lu::JSAB
{
	class MusicManager : public Script
	{
	public:
		MusicManager() {}
		virtual ~MusicManager(){}

		virtual void OnMusicEnd() = 0;
		virtual void OnStageEnd();
	protected:
		std::wstring mNextScene;
	};
} 