#pragma once
#include "LScript.h"

namespace lu
{
	class AudioSource;
}

namespace lu::JSAB
{
	class TutorialMusicController : public Script
	{
	public:
		TutorialMusicController();

		virtual void Initialize() override;
		virtual void Update() override;
		void Play();
	private:
		AudioSource* mAudioSource;
		std::vector<std::pair<double, double>> mCheckPoints;
		double mEndTime;
		double mTime;
		int mIdx;
		bool mbIsPlaying;
	};
}

