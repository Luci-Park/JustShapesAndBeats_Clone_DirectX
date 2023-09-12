#include "TitleObject.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "LAnimator.h"
#include "LObject.h"
namespace lu::JSAB
{
	void TitleObject::Initialize()
	{
		auto img = object::Instantiate<GameObject>(mTransform, eLayerType::UI);
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"TitleMat");
		if (mat == nullptr)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"Title_Fill"));
			Resources::Insert(L"TitleMat", mat);
			mat->SetRenderingMode(eRenderingMode::Transparent);
		}

		MeshRenderer* mr = img -> AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(mat);

		Vector3 scale = mat->GetTexture()->GetSize();
		mTransform->SetScale(scale * 0.5);
		orgScale = scale;

		auto anim = img -> AddComponent<Animator>();
		mAnim = anim;
		auto a = anim->CreateAnimation(L"Bump");
		float spb = 0.435;
		a->AddLocalPositionKey(spb * 0.8, Vector3::Zero);
		a->AddLocalPositionKey(spb, Vector3::Up * 30);
		a->AddLocalPositionKey(spb * 1.3, Vector3::Zero);
		a->AddLocalScaleKey(spb * 1.8, Vector3::One);
		a->AddLocalScaleKey(spb * 2, Vector3::One * 1.1);
		a->AddLocalScaleKey(spb * 2.2, Vector3::One);
		//a->AddLocalPositionKey(spb * 2.5, Vector3::Zero);
	}
	void TitleObject::OnBeat()
	{
		mAnim->PlayAnimation(L"Bump", true);
		/*if (beat)
			mAnim->PlayAnimation(L"Beat", false);
		else
			mAnim->PlayAnimation(L"Bump", false);
		beat = !beat;*/
	}

	void TitleObject::SetScaleToOrg()
	{
		mTransform->SetScale(orgScale);
	}
}