#include "EightSideBullet.h"
#include "LMeshRenderer.h"
#include "LResources.h"
namespace lu::JSAB
{
	EightSideBullet::EightSideBullet()
	{
	}
	EightSideBullet::~EightSideBullet()
	{
	}
	void EightSideBullet::Initialize()
	{
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"OctaMat");
		if (mat == nullptr)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"octa_circle_bullet"));
			mat->SetRenderingMode(eRenderingMode::CutOut);
			Resources::Insert(L"OctaMat", mat);
		}
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(mat);

		GameObject::Initialize();

	}
}