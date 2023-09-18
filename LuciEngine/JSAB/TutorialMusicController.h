#pragma once
#include "MusicController.h"

namespace lu
{
	class AudioSource;
}

namespace lu::JSAB
{
	class TutorialMusicController : public MusicController
	{
	public:
		TutorialMusicController();

		virtual void Initialize() override;
		virtual void Update() override;
		void PlayNextPart();
		double GetDiff();
	private:
	};
}

