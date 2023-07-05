#include "MenuButtonObject.h"
#include "LMeshRenderer.h"
#include "LResources.h"

namespace lu::JSAB::Menu
{
	void MenuButtonObject::Initialize()
	{
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"MenuBeatMat");
		mat->SetTexture(Resources::Find<Texture>(L"Menu_Tag"));
		mat->SetRenderingMode(eRenderingMode::CutOut);
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(mat);

		float height = 13;
		mTransform->SetPosition(Vector3(45, 0, 2));
		mTransform->SetScale(Vector3(height, height, 1));
	}
}