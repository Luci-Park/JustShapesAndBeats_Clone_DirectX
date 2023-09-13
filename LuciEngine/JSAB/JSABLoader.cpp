#include "JSABLoader.h"
#include "LResources.h"
#include "LTexture.h"
#include "LAudioClip.h"
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
namespace lu::JSAB
{
	void LoadImgs(const fs::path& directory)
	{		
		for (auto& dir : fs::directory_iterator(directory))
		{
			if (fs::is_directory(dir))
			{
				LoadImgs(dir.path());
			}
			else if (fs::is_regular_file(dir))
			{
				std::wstring filename = dir.path().stem().wstring();
				Resources::Load<lu::graphics::Texture>(filename, dir.path());
			}
		}
	}

	void LoadAudios(const fs::path& directory)
	{
		for (auto& dir : fs::directory_iterator(directory))
		{
			if (fs::is_directory(dir))
			{
				std::wstring str = dir.path().stem().wstring();
				if (dir.path().stem().wstring() == L"Not Used") continue;
				LoadAudios(dir.path());
			}
			else if (fs::is_regular_file(dir))
			{
				std::wstring filename = dir.path().stem().wstring();
				Resources::Load<lu::AudioClip>(filename, dir.path());
			}
		}
	}
	void InitializeGraphics()
	{
		const fs::path root = "..\\..\\Assets\\Texture";
		LoadImgs(root);
	}
	void InitializeAudios()
	{
		const fs::path root = "..\\..\\Assets\\AudioClips";
		LoadAudios(root);
	}
	void LoadAssets()
	{
		InitializeGraphics();
		InitializeAudios();
	}
}