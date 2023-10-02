#pragma once
#include "MusicManager.h"
#include "BulletPool.h"
namespace lu::JSAB
{
	class CheckPoint;
	class TryThisManager : public MusicManager
	{
	public:
		TryThisManager();
		virtual ~TryThisManager() {}

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Play() override;
		virtual void OnMusicEnd() override;
	private:
		CheckPoint* mCheckPoint;

	};
}

