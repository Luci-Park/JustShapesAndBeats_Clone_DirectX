#include "TrianglePrefab.h"
#include "LObject.h"
#include "LResources.h"
#include "LMeshRenderer.h"
#include "LAnimator.h"
#include "LCollider2D.h"
#include "LAudioSource.h"
#include "Triangle.h"
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
		auto t = AddComponent<Triangle>();
		t->SetClips(Resources::Find<AudioClip>(L"SFX_HEX_LEVEL_COMPLETE_TUTO_SILENCE"),
			Resources::Find<AudioClip>(L"SFX_HEX_LEVEL_COMPLETE_CHALLENGE"));
		{
			GameObject* triangle = object::Instantiate<GameObject>(mTransform, eLayerType::Item);
			triangle->SetName(L"triangle");
			MeshRenderer* mr = triangle->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(CreateTriangleMat());

			auto animator = triangle->AddComponent<Animator>();
			auto anim = animator->CreateAnimation(L"Burst");
			double downDuration = 0.1;
			double readyduration = 6.928 - downDuration;
			float y = 100.f;
			anim->AddLocalPositionKey(0, Vector3::Zero);
			anim->AddLocalPositionKey(readyduration * 0.3, { 0, y * 0.8f, 0 });
			anim->AddLocalPositionKey(readyduration, { 0, y, 0 });
			anim->AddLocalPositionKey(readyduration + downDuration, { 0, 0, 0 });

			anim->AddLocalRotationKey(0, Quaternion::Identity);
			anim->AddLocalRotationKey(readyduration * 0.3, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI *0.9));
			anim->AddLocalRotationKey(readyduration, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI));
			anim->AddLocalRotationKey(readyduration + downDuration, Quaternion::Identity);
			anim->AddFunctionKey(readyduration + downDuration, std::bind(&Triangle::OnTutoBurst, t));

			anim = animator->CreateAnimation(L"GeneralBurst");
			anim->AddLocalPositionKey(0, Vector3::Zero);
			anim->AddLocalPositionKey(readyduration * 0.3, { 0, y * 0.8f, 0 });
			anim->AddLocalPositionKey(readyduration, { 0, y, 0 });
			anim->AddLocalPositionKey(readyduration + downDuration, { 0, 0, 0 });

			anim->AddLocalRotationKey(0, Quaternion::Identity);
			anim->AddLocalRotationKey(readyduration * 0.3, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI * 0.9));
			anim->AddLocalRotationKey(readyduration, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI));
			anim->AddLocalRotationKey(readyduration + downDuration, Quaternion::Identity);
			anim->AddFunctionKey(readyduration + downDuration, std::bind(&Triangle::OnLevelComplete, t));

			anim = animator->CreateAnimation(L"Idle");
			
			float time = 0;
			for (int i = 0; i < 3; i++)
			{
				anim->AddLocalRotationKey(time, Quaternion::Identity);
				anim->AddLocalRotationKey(time += 0.2, Quaternion::CreateFromAxisAngle(Vector3::Forward, XMConvertToRadians(-35)));
				anim->AddLocalRotationKey(time += 0.1, Quaternion::CreateFromAxisAngle(Vector3::Forward, XMConvertToRadians(-40)));
				anim->AddLocalRotationKey(time += 0.05, Quaternion::CreateFromAxisAngle(Vector3::Forward, XMConvertToRadians(-40)));
				anim->AddLocalRotationKey(time += 0.1, Quaternion::CreateFromAxisAngle(Vector3::Forward, XMConvertToRadians(-35)));
				anim->AddLocalRotationKey(time += 0.2, Quaternion::Identity);
				anim->AddLocalRotationKey(time += 0.2, Quaternion::CreateFromAxisAngle(Vector3::Forward, XMConvertToRadians(35)));
				anim->AddLocalRotationKey(time += 0.1, Quaternion::CreateFromAxisAngle(Vector3::Forward, XMConvertToRadians(40)));
				anim->AddLocalRotationKey(time += 0.05, Quaternion::CreateFromAxisAngle(Vector3::Forward, XMConvertToRadians(40)));
				anim->AddLocalRotationKey(time += 0.1, Quaternion::CreateFromAxisAngle(Vector3::Forward, XMConvertToRadians(35)));
				anim->AddLocalRotationKey(time += 0.2, Quaternion::Identity);
			}
			anim->AddLocalPositionKey(time, Vector3::Zero);
			anim->AddLocalRotationKey(time, Quaternion::Identity);
			anim->AddLocalPositionKey(time += 0.25, { 0, 150 * 0.9f, 0 });
			anim->AddLocalPositionKey(time += 0.1, { 0, 150, 0 });
			anim->AddLocalRotationKey(time, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI));
			anim->AddLocalPositionKey(time += 0.05, { 0, 150, 0 });
			anim->AddLocalPositionKey(time += 0.1, { 0, 150 * 0.9f, 0 });
			anim->AddLocalPositionKey(time += 0.25, { 0, 0, 0 });
			anim->AddLocalRotationKey(time, Quaternion::CreateFromAxisAngle(Vector3::Forward, -PI * 2));


			animator->PlayAnimation(L"Idle", true);



			//anim->AddLocalPositionKey(0, Vector3::Zero);
			//anim->AddLocalPositionKey(readyduration * 0.5, { 0, 50, 0 });
		}
		{
			GameObject* circle = object::Instantiate<GameObject>(mTransform, eLayerType::Item);
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
		AddComponent<AudioSource>();
		t->Setup();
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
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"TriangleEffect_White_Mat");
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
		std::shared_ptr<Material> mat = Resources::Find<Material>(L"TriangleEffect_Blue_Mat");
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