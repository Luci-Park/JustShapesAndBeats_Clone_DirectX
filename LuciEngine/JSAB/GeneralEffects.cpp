#include "GeneralEffects.h"
#include "LMaterial.h"
#include "LResources.h"
namespace lu::JSAB
{
	std::shared_ptr<Material> GetGeneralMaterial(const std::wstring key)
	{
		auto mat = Resources::Find<Material>(key);
		if (mat == nullptr)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			auto t = Resources::Find<Texture>(key);
			assert(t != nullptr);
			mat->SetTexture(t);
			mat->SetRenderingMode(eRenderingMode::CutOut);
			Resources::Insert(key, mat);
			mat->SetKey(key);
		}
		return mat;
	}
}