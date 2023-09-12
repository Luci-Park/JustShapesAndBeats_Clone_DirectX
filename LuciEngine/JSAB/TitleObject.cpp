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
		auto light = object::Instantiate<GameObject>(mTransform, eLayerType::UI);
		auto lightanim = light->AddComponent<Animator>();
		auto ani = lightanim->CreateAnimation(L"Appear");
		double duration = 0.1;
		ani->AddLocalScaleKey(0, Vector3::Zero);
		ani->AddLocalRotationKey(0, Quaternion::Identity);
		ani->AddLocalRotationKey(duration * 0.5, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI));
		ani->AddLocalScaleKey(duration * 0.5, Vector3::One);
		ani->AddLocalRotationKey(duration, Quaternion::CreateFromAxisAngle(Vector3::Forward, -2*PI));
		ani->AddLocalScaleKey(duration, Vector3::Zero);

		MeshRenderer* mr = img -> AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(mat);
		mat->SetTint({ 0.3, 0.3, 0.3, 0.3 });

		Vector3 scale = mat->GetTexture()->GetSize();
		mTransform->SetScale(scale * 0.5);
		orgScale = scale * 0.5;

		mAnim = AddComponent<Animator>();
		auto an = mAnim->CreateAnimation(L"Fade In");
		an->AddScaleKey(0, Vector3::Zero);
		an->AddScaleKey(5, orgScale * 0.3);

		an = mAnim->CreateAnimation(L"Appear");
		an->AddScaleKey(0, orgScale * 0.4);
		an->AddScaleKey(0.3, orgScale);

		auto anim = img -> AddComponent<Animator>();
		mImgAnim = anim;
		auto a = anim->CreateAnimation(L"Bump");
		float spb = 0.435;
		a->AddLocalPositionKey(spb * 0.8, Vector3::Zero);
		a->AddLocalPositionKey(spb, Vector3::Up * 30);
		a->AddLocalPositionKey(spb * 1.3, Vector3::Zero);
		a->AddLocalScaleKey(spb * 1.8, Vector3::One);
		a->AddLocalScaleKey(spb * 2, Vector3::One * 1.1);
		a->AddLocalScaleKey(spb * 2.2, Vector3::One);
	}
	void TitleObject::OnBeat()
	{

		mImgAnim->PlayAnimation(L"Bump", true);
		mAnim->PlayAnimation(L"Appear", false);
		mImgAnim->Owner()->GetComponent<MeshRenderer>()->GetMaterial()->SetTint(Color::white);
	}

	void TitleObject::OnAppear()
	{
		mAnim->PlayAnimation(L"Fade In", false);
		mImgAnim->PlayAnimation(L"Bump", true);

	}
}