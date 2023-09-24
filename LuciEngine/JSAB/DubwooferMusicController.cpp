#include "DubwooferMusicController.h"
#include "LInput.h"
namespace lu::JSAB
{
	DubwooferMusicController::DubwooferMusicController()
	{
        mCheckPoints = {
            std::make_pair(0, 27.75),
            std::make_pair(27.75, 54.25),
            std::make_pair(54.25, 92.4),
            std::make_pair(92.4, 131.15),
            std::make_pair(131.15, 159.95),
        };
	}

	void DubwooferMusicController::Initialize()
	{
		MusicController::Initialize();
		SetClip(L"mus_dubwoofer_substep");
	}

	void DubwooferMusicController::Update()
	{
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			mStageIdx = 2;
			mAudioSource->SetPosition(120);
		}
		MusicController::Update();
		if (GetTime() >= 159.95)
			Finish();
	}

}