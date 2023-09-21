#include "DubwooferWaterBullet.h"
#include "LGameObject.h"
#include "LMeshRenderer.h"
#include "LCollider2D.h"
#include "LAnimator.h"
#include "LResources.h"
#include "LObject.h"
namespace lu::JSAB
{
	void DubwooferWaterBullet::Initialize()
	{
		Script::Initialize();
		mAnim = Owner()->AddComponent<Animator>();
		mMr = Owner()->AddComponent<MeshRenderer>();
		mPs = Owner()->AddComponent<ParticleSystem>();
		mCol = Owner()->AddComponent<Collider2D>();

		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mMr->SetMaterial(Resources::Load<Material>(L"DWWaterMat", L"DB_Water"));
		mMr->GetMaterial()->SetRenderingMode(eRenderingMode::CutOut);

		mTransform->SetScale(10, 300, 1);
	}
}