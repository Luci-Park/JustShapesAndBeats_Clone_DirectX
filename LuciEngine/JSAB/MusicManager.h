#pragma once
#include "..\\Engine_SOURCE\\LScript.h"
#include "MusicController.h"
#include "Triangle.h"
namespace lu::JSAB
{
	class MusicManager : public Script
	{
	public:
		static MusicManager* Instance;
		MusicManager();
		virtual ~MusicManager(){}

		virtual void Update() override;

		virtual void Play();
		virtual void OnMusicEnd() = 0;
		virtual void OnLevelEnd();
	protected:
		MusicController* mMusic;
		InGameTriangle* mLevelTriangle;

		std::wstring mNextScene;
		double mLevelEndCounter;
		double mTriangleAppearTime;
		bool mbFin;
	};
} 