#include "JSABRenderer.h"
#include "LResources.h"
#include "LTexture.h"
#include "LMaterial.h"
#include "LShader.h"
namespace lu::JSAB
{
	void LoadBackground()
	{		
		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");

		std::wstring folderPath = L"..\\..\\Assets\\Texture\\Background\\";
		std::vector<std::wstring> imgs = {
			L"black_background",
			L"darkblue_background",
			L"green_background",
			L"grey_background",
			L"turquoise_background",
			L"pink_background",
			L"purple_background",
			L"skyblue_background",
			L"white_background",
			L"annihilate_background"
		};

		for (int i = 0; i < imgs.size(); i++)
		{
			std::wstring filepath = folderPath + imgs[i] + L".png";
			std::shared_ptr<Texture> tex = Resources::Load<Texture>(imgs[i], filepath);
		}
	}

	void LoadPlayer()
	{
		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
		std::wstring folderPath = L"..\\..\\Assets\\Texture\\Player\\Player\\";
		std::wstring img = L"player";
		for (int i = 1; i <= 77; i++)
		{
			std::wstring filename = folderPath + img + std::to_wstring(i) + L".png";
			Resources::Load<Texture>(img + std::to_wstring(i), filename);
		}
	}
	void InitializeGraphics()
	{
		LoadBackground();
		LoadPlayer();
	}
}