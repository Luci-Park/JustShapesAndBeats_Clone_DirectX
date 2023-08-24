#pragma once
#include "LScript.h"

namespace lu
{
	class AudioSource;
}
namespace lu::JSAB
{
	class MusicController : public Script
	{
	public:
		static MusicController* _MusicController;
		MusicController();
		~MusicController(){}
		virtual void Initialize() override;
		virtual void Update() override;
		void Play();
		double GetTime();
	protected:
		AudioSource* mAudioSource;
		std::vector<std::pair<double, double>> mCheckPoints;
		double mEndTime;
		float mFadeDuration;
		float mFadeTime;
		float mStartVolume;
		int mStageIdx;
		int mNextStageIdx;
		bool mbIsPlaying;
	};
}

