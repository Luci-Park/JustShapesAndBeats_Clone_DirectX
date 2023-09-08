#include "TrianglePrefab.h"
#include "LObject.h"
#include "LResources.h"
#include "LMeshRenderer.h"
#include "LAnimator.h"
#include "LCollider2D.h"
namespace lu::JSAB
{
	TrianglePrefab::TrianglePrefab(eLayerType layer)
		:GameObject(layer)
	{
	}
	TrianglePrefab::~TrianglePrefab()
	{
	}
	void TrianglePrefab::Initialize()
	{
		SetName(L"CheckPointTriangle");
		mTransform->SetScale({ 26, 26, 1 });
		mTransform->SetPosition({ 50,50, 1 });
		AddComponent<Collider2D>()->SetType(lu::enums::eColliderType::Circle)->SetSize({ 2.3, 2.3 });
		{
			GameObject* triangle = object::Instantiate<GameObject>(mTransform, eLayerType::FriendlyObjects);
			triangle->SetName(L"triangle");
			MeshRenderer* mr = triangle->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(CreateTriangleMat());
		}

		{
			GameObject* circle = object::Instantiate<GameObject>(mTransform, eLayerType::FriendlyObjects);
			circle->SetName(L"tri_effect_blue");
			MeshRenderer* mr = circle->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(CreateWhiteBlueCircleMat());
			circle->mTransform->SetLocalScale({ 2, 2, 1 });
			Animator* anim = circle->AddComponent<Animator>();
			Animation* ani = anim->CreateAnimation(L"Rotate");

			float duration = 1.0f;
			ani->AddRotationKey(0, Quaternion::Identity);
			ani->AddRotationKey(duration * .25, Quaternion::CreateFromAxisAngle(Vector3::Forward, PI * 0.5));
			ani->AddRotationKey(duration * .5, Quaternion::CreateFromAxisAngle(Vector3::Forward, PI));
			ani->AddRotationKey(duration * .75, Quaternion::CreateFromAxisAngle(Vector3::Forward, PI * 1.5));
			ani->AddRotationKey(duration, Quaternion::CreateFromAxisAngle(Vector3::Forward, PI * 2));
			anim->PlayAnimation(L"Rotate", true);
		}
		{
			GameObject* circle = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
			circle->SetName(L"tri_effect_white");
			MeshRenderer* mr = circle->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(CreateWhiteCircleMat());
			circle->mTransform->SetLocalScale({ 2.3, 2.3, 1 });
			Animator* anim = circle->AddComponent<Animator>();
			Animation* ani = anim->CreateAnimation(L"Rotate");
			ani->AddRotationKey(0, Quaternion::Identity);

			float duration = 1.0f;
			ani->AddRotationKey(0, Quaternion::Identity);
			ani->AddRotationKey(duration * .25, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI * 0.5));
			ani->AddRotationKey(duration * .5, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI));
			ani->AddRotationKey(duration * .75, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI * 1.5));
			ani->AddRotationKey(duration, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI * 2));
			anim->PlayAnimation(L"Rotate", true);
		}
	}
	std::shared_ptr<graphics::Material> TrianglePrefab::CreateTriangleMat()
	{
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"Triangle");
		if (!mat)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"Triangle"));
			mat->SetRenderingMode(eRenderingMode::CutOut);
			Resources::Insert(L"Triangle", mat);
		}
		return mat;
	}
	std::shared_ptr<graphics::Material> TrianglePrefab::CreateWhiteCircleMat()
	{
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"TriangleEffect_White");
		if (!mat)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"TriangleEffect"));
			mat->SetRenderingMode(eRenderingMode::CutOut);
			Resources::Insert(L"TriangleEffect_White", mat);
		}
		return mat;
	}
	std::shared_ptr<graphics::Material> TrianglePrefab::CreateWhiteBlueCircleMat()
	{
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"TriangleEffect_Blue");
		if (!mat)
		{
			mat = std::make_shared<Material>();
			mat->SetShader(Resources::Find<Shader>(L"SpriteShader"));
			mat->SetTexture(Resources::Find<Texture>(L"TriangleEffect_Flip"));
			mat->SetRenderingMode(eRenderingMode::CutOut);
			mat->SetTint({ 0, 1, 1, 1 });
			Resources::Insert(L"TriangleEffect_Blue", mat);
		}
		return mat;
	}
}