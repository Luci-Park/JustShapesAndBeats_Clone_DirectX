#include "DubwooferSpikeBullet.h"
#include "LGameObject.h"
#include "LMeshRenderer.h"
#include "LCollider2D.h"
#include "LAnimator.h"
#include "LResources.h"
#include "LRigidBody.h"
#include "LObject.h"
namespace lu::JSAB
{
	void DubwooferSpikeBullet::Initialize()
	{
		Script::Initialize();
		float width = 60.f;

		Owner()->AddComponent<Collider2D>();
		auto mr = Owner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Load<Material>(L"DWSpikeMat", L"DB_Ceiling"));
		mr->GetMaterial()->SetRenderingMode(eRenderingMode::Transparent);
		auto tex = mr->GetMaterial()->GetTexture();

		mTransform->SetScale(110, 100, 1);
		mTransform->SetRotation(Quaternion::Create2DRotationDegrees(180));

		auto g = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet);
		mr = g->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Load<Material>(L"DWSpikeHoleMat", L"DB_CeilingHole"));
		mr->GetMaterial()->SetRenderingMode(eRenderingMode::Transparent);

		g->mTransform->SetLocalPosition(0, 0, 0.1);


	}
}