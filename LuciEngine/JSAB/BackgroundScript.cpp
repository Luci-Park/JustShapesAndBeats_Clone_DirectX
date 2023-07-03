#include "BackgroundScript.h"
#include "LMaterial.h"
#include "LResources.h"
#include "LGameObject.h"
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
		mMeshRenderer->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
	}
	void BackgroundScript::SetBackground(Backgrounds type)
	{
		if (type >= Backgrounds::END)
			type = Backgrounds::BLACK;
		mMeshRenderer->SetMaterial(_backgrounds[(int)type]);
	}
	void BackgroundScript::SetBackground(int type)
	{
		if (type < 0 || type >= (int)Backgrounds::END)
			type = 0;
		mMeshRenderer->SetMaterial(_backgrounds[type]);
	}
}