#include "TryThisSpotlight.h"
namespace lu::JSAB
{
	void TryThisSpotlight::BulletSetUp()
	{
		auto mesh = Resources::Find<Mesh>(L"RectMesh");
		auto mat = Resources::Load<Material>(L"circle_bullet_prep", L"circle_bullet_prep");
		auto mr = Owner()->AddComponent<MeshRenderer>();
		mr->SetMesh(mesh)->SetMaterial(mat);
		mat->SetRenderingMode(eRenderingMode::CutOut);


		auto mat = Resources::Load<Material>(L"SpotlightFill", L"circle_bullet"); 
		mat->SetRenderingMode(eRenderingMode::Transparent);
		mFillMr->SetMesh(mesh)->SetMaterial(mat);
		mFillMr->SetColor(Color::white);
	}
	void TryThisSpotlight::OnWarning()
	{
	}
	void TryThisSpotlight::WhileWarning(double time)
	{
	}
	void TryThisSpotlight::OnActivate()
	{
	}
	void TryThisSpotlight::WhileActivate(double time)
	{
	}
	void TryThisSpotlight::OnOutro()
	{
	}
	void TryThisSpotlight::WhileOutro(double time)
	{
	}
	void TryThisSpotlight::OnDeActivate()
	{
	}
}