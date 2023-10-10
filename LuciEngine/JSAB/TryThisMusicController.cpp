#include "TryThisMusicController.h"
#include "LInput.h"
namespace lu::JSAB
{
	TryThisMusicController::TryThisMusicController()
	{
	}
	void TryThisMusicController::Initialize()
	{
		MusicController::Initialize();
		SetClip(L"mus_try_this");
	}
	void TryThisMusicController::Update()
	{
		MusicController::Update();
	}
}