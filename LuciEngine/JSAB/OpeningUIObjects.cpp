#include "OpeningUIObjects.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "LAnimator.h"
namespace lu::JSAB::Title
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
			mat->SetRenderingMode(eRenderingMode::Transparent);
		}

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(mat);

		Vector3 scale = Vector3::One;
		scale.y = 40;
		scale.x = mat->GetTexture()->GetRatioWidth(scale.y);
		mTransform->SetScale(scale);

		mTransform->SetPosition(Vector3(-60, 0, 3));

		auto anim = AddComponent<Animator>();
		auto an = anim->CreateAnimation(L"Fade In");
		an->AddTintKey(0, Color::clear);
		an->AddTintKey(0.3, Color::white);
		an = anim->CreateAnimation(L"Beat");
		an->AddScaleKey(0, scale);
		an->AddScaleKey(0.2, scale * 1.5);
		an->AddScaleKey(0, scale);
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
			mat->SetRenderingMode(eRenderingMode::Transparent);
		}

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(mat);
		mat->SetTint({ 1, 1, 1, 0.5f });

		Vector3 scale = Vector3::One;
		scale.y = 25;
		scale.x = mat->GetTexture()->GetRatioWidth(scale.y);
		mTransform->SetScale(scale);
		mTransform->SetPosition(Vector3(0, 0, 3));
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
			mat->SetRenderingMode(eRenderingMode::Transparent);
		}

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(mat);

		Vector3 scale = Vector3::One;
		scale.y = 40;
		scale.x = mat->GetTexture()->GetRatioWidth(scale.y);
		mTransform->SetScale(scale);

		mTransform->SetPosition(Vector3(53, 0, 3));
	}

	void LightCircleObject::Initialize()
	{
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"MenuLightMat");
		if (mat == nullptr)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"Title_Effect_C"));
			Resources::Insert(L"MenuLightMat", mat);
			mat->SetRenderingMode(eRenderingMode::Transparent);
		}

		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(mat);

		Vector3 scale = mat->GetTexture()->GetSize();
		mTransform->SetScale(scale * 0.5);
		mTransform->SetPosition(Vector3(0, 0, 2));
	}

}	