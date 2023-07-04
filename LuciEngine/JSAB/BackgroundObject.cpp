#include "BackgroundObject.h"
#include "LMeshRenderer.h"
#include "LResources.h"

namespace lu::JSAB
{
	BackgroundObject::BackgroundObject()
	{
	}
	BackgroundObject::~BackgroundObject()
	{
	}
	void BackgroundObject::Initialize()
	{
		mTransform->SetPosition(Vector3(0, 0, 10));		
		mTransform->SetScale(Vector3(8, 6, 1));
		
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"BackgroundMat");
		if (mat == nullptr)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			Resources::Insert(L"BackgroundMat", mat);
		}

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(mat);

		mBackground = AddComponent<BackgroundScript>();
		GameObject::Initialize();
	}
	void BackgroundObject::SetBackground(BackgroundScript::Backgrounds bg)
	{
		mBackground->SetBackground(bg);
	}
}