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
		static MusicController* Instance;
		MusicController();
		~MusicController(){}
		virtual void Initialize() override;
		virtual void Update() override;
		void Play();
		double GetTime();
		int GetStage() { return mStageIdx; }
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

