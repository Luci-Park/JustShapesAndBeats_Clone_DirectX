#include "BackgroundObject.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "LApplication.h"

extern lu::Application application;

namespace lu::JSAB
{
	BackgroundObject::BackgroundObject(eLayerType layer)
		:GameObject(layer)
	{
	}
	BackgroundObject::~BackgroundObject()
	{
	}
	void BackgroundObject::Initialize()
	{		
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

		AddComponent<BackgroundScript>();

		GameObject::Initialize();
		mTransform->SetPosition(Vector3(0, 0, 10));		
		mTransform->SetScale(Vector3(application.GetWidth(), application.GetHeight(), 1));
	}
}