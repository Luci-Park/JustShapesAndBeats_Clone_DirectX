#include "TryThisSpotlight.h"

namespace lu::JSAB
{
	void TryThisSpotlight::BulletSetUp()
	{
		mReadySprite = Resources::Find<Texture>(L"circle_bullet_prep");
		mActivateSprite = Resources::Find<Texture>(L"An_BurstEffect");
		mOutlineSprite = Resources::Find<Texture>(L"circle_bullet_prep");
		auto mesh = Resources::Find<Mesh>(L"RectMesh");
		mWarning = object::Instantiate<GameObject>(eLayerType::Bullet);
		auto mr = mWarning->AddComponent<MeshRenderer>();
		mr->SetMesh(mesh);

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