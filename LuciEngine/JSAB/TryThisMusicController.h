#pragma once
#include "MusicController.h"

namespace lu::JSAB
{
	class TryThisMusicController : public MusicController
	{
	public:
		TryThisMusicController();
		virtual void Initialize() override;
		virtual void Update() override;
	};
}

