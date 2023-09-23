#include "TutorialMusicController.h"
#include "LGameObject.h"
#include "LTime.h"
#include "LFontWrapper.h"
#include "LInput.h"
#include "TutorialManager.h"
#include "LText.h"
namespace lu::JSAB
{
	TutorialMusicController::TutorialMusicController()
	{
        mCheckPoints = {
            std::make_pair(0.763, 7.691),
            std::make_pair(7.691, 14.619),
            std::make_pair(14.619, 21.547),
            std::make_pair(28.475, 35.403),
            std::make_pair(35.403, 42.331),
            std::make_pair(42.331, 49.259),
            std::make_pair(56.187, 63.115),
            std::make_pair(70.043, 76.971),
            std::make_pair(111.611, 160.107)
        };
		mEndTime = mCheckPoints[8].second;
	}

	void TutorialMusicController::Initialize()
	{
		MusicController::Initialize();
		SetClip(L"mus_corrupted");
	}
	
	void TutorialMusicController::Update()
	{
		if (mbIsPlaying)
		{
			double time = mAudioSource->GetPosition();
			mText->text = std::to_wstring(time);
			if (time < mEndTime)
			{
				if (time > mCheckPoints[mStageIdx].second)
				{
					if (mNextStageIdx > mStageIdx)
					{
						mStageIdx = mNextStageIdx;
						Owner()->GetComponent<TutorialManager>()->OnStageChange(mStageIdx);
					}
					if (mStageIdx < mCheckPoints.size())
						mAudioSource->SetPosition(mCheckPoints[mStageIdx].first);
					else
						Finish();
				}
			}
		}
		if (Input::GetKeyDown(eKeyCode::Q))
			PlayNextPart();
	}
	void TutorialMusicController::PlayNextPart()
	{
		if (mNextStageIdx < mCheckPoints.size() - 1)
			mNextStageIdx++;		
	}
	double TutorialMusicController::GetDiff()
	{
		return mCheckPoints[mStageIdx].second - GetTime();
	}
}