#pragma once
#include "..\\Engine_SOURCE\LScript.h"
#include "..\\Engine_SOURCE\LAudioSource.h"
namespace lu
{
	class Text;
}
namespace lu::JSAB
{
	class MusicController : public Script
	{
	public:
		static MusicController* Instance;
		MusicController();
		~MusicController(){}
		void SetClip(std::wstring clip);
		virtual void Initialize() override;
		virtual void Update() override;
		void Play();
		void Stop();
		void Finish() { mbIsFinishing = true; }
		double GetTime();
		int GetStage() { return mStageIdx; }
		float GetPercent();
		bool IsPlaying() { return mbIsPlaying && !mbIsFinishing; }
	protected:
		AudioSource* mAudioSource;
		Text* mText;
		std::vector<std::pair<double, double>> mCheckPoints;
		float mFadeDuration;
		float mFadeTime;
		float mStartVolume;
		int mStageIdx;
		int mNextStageIdx;
		bool mbIsPlaying;
		bool mbIsFinishing;
	};
}

