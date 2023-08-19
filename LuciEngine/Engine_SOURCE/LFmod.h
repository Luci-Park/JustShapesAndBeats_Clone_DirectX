#pragma once
#include "LuciEngine.h"

#include "..\\Extern\\Fmod\\Include\\fmod_studio.hpp"
#include "..\\Extern\\Fmod\\Include\\fmod.hpp"
#include "..\\Extern\\Fmod\\Include\\fmod_common.h"
#include "..\\Extern\\Fmod\\Include\\fmod_codec.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Extern\\Fmod\\Library\\Debug\\fmodL_vc.lib")
#pragma comment(lib, "..\\Extern\\Fmod\\Library\\Debug\\fmodstudioL_vc.lib")
#else						   
#pragma comment(lib, "..\\Extern\\Fmod\\Library\\Debug\\fmod_vc.lib")
#pragma comment(lib, "..\\Extern\\Fmod\\Library\\Release\\fmodstudio_vc.lib")
#endif
namespace lu
{
	using namespace math;
	class Fmod
	{
	public:
		static void Initialize();
		static bool CreateSound(const std::string& path, FMOD::Sound** sound);
		static void SoundPlay(FMOD::Sound* sound, FMOD::Channel** channel);
		static void Set3DListenerAttributes(const Vector3* pos, const Vector3* vel, const Vector3* forward, const Vector3* up);
		static void Release();

	private:
		static FMOD::Studio::System* mSystem;
		static FMOD::System* mCoreSystem;
	};
}

