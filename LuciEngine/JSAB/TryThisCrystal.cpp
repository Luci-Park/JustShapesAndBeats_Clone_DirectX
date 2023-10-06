#include "TryThisCrystal.h"
#include "LTime.h"
namespace lu::JSAB
{
	void TryThisCrystal::BulletSetUp()
	{
		auto mr = Owner()->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Load<Material>(L"CaseMat", L"TT_Case"));
		Vector3 scale;
		scale.y = 300;
		scale.z = 1;
		scale.x = mr->GetMaterial()->GetTexture()->GetRatioWidth(scale.y);
		mTransform->SetScale(scale);
		
	}
	void TryThisCrystal::OnWarning()
	{
	}
	void TryThisCrystal::WhileWarning(double time)
	{
	}
	void TryThisCrystal::OnActivate()
	{
	}
	void TryThisCrystal::WhileActivate(double time)
	{
		Vector3 pos = mTransform->GetPosition();
		pos.x = RealRandom<float>(-1.0, 1.0) * 2;
		pos.y -= 10 * Time::DeltaTime();
		
		mTransform->SetPosition(pos);
		if (pos.y < (- 360 - 0.5 * mTransform->GetScale().y))
			DeActivate();
	}
	void TryThisCrystal::OnOutro()
	{
	}
	void TryThisCrystal::WhileOutro(double time)
	{
	}
	void TryThisCrystal::OnDeActivate()
	{
	}
}