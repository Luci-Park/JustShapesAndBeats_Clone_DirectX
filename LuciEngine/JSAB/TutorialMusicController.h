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
		void PlayNextPart();
		double GetTime() { return mTime; }
	private:
		AudioSource* mAudioSource;
		std::vector<std::pair<double, double>> mCheckPoints;
		double mEndTime;
		double mTime;
		float mFadeDuration;
		float mFadeTime;
		float mStartVolume;
		int mIdx;
		int mNextIdx;
		bool mbIsPlaying;
	};
}

