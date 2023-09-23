#include "DubwooferWaterBullet.h"
#include "DubwooferWater.h"
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
		Owner()->SetTag(eTagType::Bullet);

	}
	void DubwooferWaterBullet::SetY(float y)
	{
		Vector3 currScale = mTransform->GetScale();
		mTransform->SetScale(currScale.x, y, currScale.z);
	}
	void DubwooferWaterBullet::OnCollisionEnter(Collider2D* other)
	{
		if (other->Owner()->GetLayer() == eLayerType::Bullet)
			mBody->OnImpact(mIdx, other->Owner()->mTransform);
	}
}