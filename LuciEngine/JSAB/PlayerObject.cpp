#include "PlayerObject.h"
#include "LMeshRenderer.h"
#include "LResources.h"

namespace lu::JSAB
{
	PlayerObject::PlayerObject()
	{
	}
	PlayerObject::~PlayerObject()
	{
	}
	void PlayerObject::Initialize()
	{
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"PlayerMat");
		if (mat == nullptr)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"player1"));
			mat->SetRenderingMode(eRenderingMode::CutOut);
			Resources::Insert(L"PlayerMat", mat);
		}

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(mat);

		mTransform->SetScale(Vector3(10, 10, 1));

		GameObject::Initialize();
	}
}