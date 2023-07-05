#include "TitleObject.h"
#include "LMeshRenderer.h"
#include "LResources.h"

namespace lu::JSAB::Menu
{
	void TitleObject::Initialize()
	{
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"TitleMat");
		if (mat == nullptr)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"Title_Fill"));
			Resources::Insert(L"TitleMat", mat);
			mat->SetRenderingMode(eRenderingMode::Transparent);
		}

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(mat);

		Vector3 scale = Vector3(45, 34, 1);
		mTransform->SetScale(scale);

		GameObject::Initialize();
	}
}