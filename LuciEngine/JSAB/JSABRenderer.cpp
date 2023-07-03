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
			std::wstring matName = imgs[i] + L"_mat";
			std::shared_ptr<Texture> tex = Resources::Load<Texture>(imgs[i], filepath);

			std::shared_ptr<Material> mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(tex);
			Resources::Insert(matName, mat);
		}
	}
	void InitializeGraphics()
	{
		LoadBackground();
	}
}