#include "JSABRenderer.h"
#include "LResources.h"
#include "LTexture.h"
#include "LMaterial.h"
#include "LShader.h"

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
				std::wstring filepath = dir.path().filename().wstring();
				std::wstring filename = dir.path().stem().wstring();
				Resources::Load<Texture>(filename, filepath);
			}
		}
	}
	void InitializeGraphics()
	{
		const fs::path root = "..\\..\\Assets\\Texture";
		LoadImgs(root);
	}
}