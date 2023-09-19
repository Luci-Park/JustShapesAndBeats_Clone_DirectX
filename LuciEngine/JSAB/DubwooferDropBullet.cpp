#include "DubwooferDropBullet.h"
#include "LGameObject.h"
#include "LMeshRenderer.h"
#include "LCollider2D.h"
#include "LAnimator.h"
#include "LResources.h"
#include "LRigidBody.h"
namespace lu::JSAB
{
	DubwooferDropBullet::DubwooferDropBullet()
		: mAnim(nullptr)
	{
	}
	void DubwooferDropBullet::Initialize()
	{
		Script::Initialize();
		Owner()->AddComponent<Collider2D>()->SetType(eColliderType::Circle);
		
		auto mr = Owner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))
			->SetMaterial(Resources::Load<Material>(L"DropBulletMat", L"SmallCircle"));

		mAnim = Owner()->AddComponent<Animator>();
		mAnim->


	}
	void DubwooferDropBullet::Update()
	{
	}
}