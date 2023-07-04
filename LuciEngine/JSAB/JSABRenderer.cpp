#include "JSABRenderer.h"
#include "LResources.h"
#include "LTexture.h"
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
	void InitializeGraphics()
	{
		const fs::path root = "..\\..\\Assets\\Texture";
		LoadImgs(root);
	}
}