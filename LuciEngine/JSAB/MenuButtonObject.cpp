#include "MenuButtonObject.h"
#include "LMeshRenderer.h"
#include "LResources.h"

namespace lu::JSAB::Menu
{
	void MenuButtonObject::Initialize()
	{
		GameObject* tag, sideTag;
		{
			std::shared_ptr<Material> mat = Resources::Find<Material>(L"MenuBeatMat");
			auto tex = Resources::Find<Texture>(L"Menu_Tag_Story_OnPoint");
			mat->SetTexture(tex);
			mat->SetRenderingMode(eRenderingMode::CutOut);
			MeshRenderer* mr = tag->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(mat);
			tag->mTransform->SetPosition(Vector3(90, 90, 2));
			tag->mTransform->SetScale(Vector3(50, 17, 1));
			tag->mTransform->SetParent(mTransform);
		}
		GameObject::Initialize();
	}
}