#include "BackgroundScript.h"
#include "LMaterial.h"
#include "LResources.h"
namespace lu::JSAB
{
	std::vector<std::shared_ptr<Material>> BackgroundScript::_backgrounds = {};
	BackgroundScript::BackgroundScript()
	{
	}
	BackgroundScript::~BackgroundScript()
	{
	}
	void BackgroundScript::Initialize()
	{
		if (_backgrounds.empty())
		{
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
			
			_backgrounds.resize(imgs.size());
			for (int i = 0; i < imgs.size(); i++)
			{
				_backgrounds[i] = Resources::Find<Material>(imgs[i] + L"_mat");
			}
		}
		mMeshRenderer = GetOwner()->GetComponent<MeshRenderer>();
	}
	void BackgroundScript::SetMaterial(Backgrounds type)
	{
		mMeshRenderer->SetMaterial(_backgrounds[(int)type]);
	}
	void BackgroundScript::SetMaterial(int type)
	{
		if (type < 0 || type >= (int)Backgrounds::END)
			type = 0;
		mMeshRenderer->SetMaterial(_backgrounds[type]);
	}
}