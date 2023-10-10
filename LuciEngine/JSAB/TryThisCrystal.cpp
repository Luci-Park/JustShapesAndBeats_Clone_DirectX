#include "TryThisCrystal.h"
#include "LTime.h"
namespace lu::JSAB
{
	void TryThisCrystal::Initialize()
	{
		Script::Initialize();
		Owner()->SetTag(eTagType::Bullet);
		auto mr = Owner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Load<Material>(L"CaseMat", L"TT_Case"));
		Vector3 scale;
		scale.y = 460.2674;
		scale.z = 1;
		scale.x = mr->GetMaterial()->GetTexture()->GetRatioWidth(scale.y);
		mTransform->SetScale(scale);
		Owner()->AddComponent<Collider2D>();
	}
	void TryThisCrystal::Update()
	{
		if (mbMove)
		{
			Vector3 pos = mTransform->GetPosition();
			pos.x = RealRandom<float>(-1.0, 1.0) * 2;
			pos.y -= 10 * Time::DeltaTime();

			mTransform->SetPosition(pos);
			if (pos.y < (-360 - 0.5 * mTransform->GetScale().y))
				mbMove = false;
		}
	}
	void TryThisCrystal::Activate()
	{
		mbMove = true;
	}
}