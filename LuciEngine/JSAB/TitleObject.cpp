#include "TitleObject.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "LAnimator.h"
#include "LObject.h"
namespace lu::JSAB
{
	void TitleObject::Initialize()
	{
		SetName(L"TitleParent");
		auto img = object::Instantiate<GameObject>(mTransform, eLayerType::UI);
		img->SetName(L"TitleObject");
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

		an = mAnim->CreateAnimation(L"Move");
		an->AddPositionKey(0, Vector3::Zero);
		an->AddScaleKey(0, orgScale);
		an->AddPositionKey(1, Vector3(-281, 0, 0));
		an->AddScaleKey(1, orgScale * 0.8);

		{
			auto anim = img->AddComponent<Animator>();
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
		{
			auto light = object::Instantiate<GameObject>(eLayerType::UI);
			light->SetName(L"TitleLight");
			auto lightanim = light->AddComponent<Animator>();
			auto ani = lightanim->CreateAnimation(L"Appear");
			double duration = 1;
			ani->AddScaleKey(0, Vector3::Zero);
			ani->AddRotationKey(0, Quaternion::Identity);
			ani->AddRotationKey(duration * 0.5, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI));
			ani->AddScaleKey(duration * 0.5, Vector3::One * orgScale.x);
			ani->AddRotationKey(duration, Quaternion::CreateFromAxisAngle(Vector3::Forward, -2 * PI));
			ani->AddScaleKey(duration, Vector3::Zero);
			light->mTransform->SetPosition({ 0, 0, 2 });

			std::shared_ptr<Material> mat = Resources::Find<Material>(L"TitleLight");
			if (mat == nullptr)
			{
				mat = std::make_shared<Material>();
				mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
				mat->SetTexture(Resources::Find<Texture>(L"Title_Effect"));
				Resources::Insert(L"TitleLight", mat);
				mat->SetRenderingMode(eRenderingMode::Transparent);
			}

			MeshRenderer* mr = light->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(mat);
			mLight = lightanim;
			light->SetActive(false);
		}
		
	}
	void TitleObject::OnBeat()
	{
		mImgAnim->PlayAnimation(L"Bump", true);
		mAnim->PlayAnimation(L"Appear", false);
		mImgAnim->Owner()->GetComponent<MeshRenderer>()->GetMaterial()->SetTint(Color::white);
		mLight->Owner()->SetActive(true);
		mLight->PlayAnimation(L"Appear", false);
	}

	void TitleObject::OnAppear()
	{
		mAnim->PlayAnimation(L"Fade In", false);
		mImgAnim->PlayAnimation(L"Bump", true);
	}
	void TitleObject::OnMove()
	{
		mAnim->PlayAnimation(L"Move", false);
	}
}