#include "OpeningUIObjects.h"
#include "LMeshRenderer.h"
#include "LResources.h"

namespace lu::JSAB::MainMenu
{
	void ShapesObject::Initialize()
	{
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"MenuShapesMat");
		if (mat == nullptr)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"Title_Shapes_White"));
			Resources::Insert(L"MenuShapesMat", mat);
		}

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(mat);

		float height = 13;
		mTransform->SetPosition(Vector3(-45, 0, 2));
		mTransform->SetScale(Vector3(height + 1, height, 1));
	}
	void AndObject::Initialize()
	{
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"MenuAndMat");
		if (mat == nullptr)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"Title_And_Gray"));
			Resources::Insert(L"MenuAndMat", mat);
		}

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(mat);

		float height = 10;
		mTransform->SetPosition(Vector3(0, 0, 2));

		mTransform->SetScale(Vector3(height, height, 1));
	}
	void BeatsObject::Initialize()
	{
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"MenuBeatMat");
		if (mat == nullptr)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"Title_Beats_White"));
			Resources::Insert(L"MenuBeatMat", mat);
		}

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(mat);

		float height = 13;
		mTransform->SetPosition(Vector3(45, 0, 2));
		mTransform->SetScale(Vector3(height, height, 1));
	}
}	