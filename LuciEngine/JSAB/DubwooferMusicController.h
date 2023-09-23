#pragma once
#include "MusicController.h"

namespace lu::JSAB
{
	class DubwooferMusicController : public MusicController
	{
	public:
		DubwooferMusicController();

		virtual void Initialize() override;
		virtual void Update() override;
	};
}

