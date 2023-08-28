#include "TutorialBeatBar.h"
#include "GeneralEffects.h"
#include "resource.h"
#include "LApplication.h"
#include "LGameObject.h"
#include "LMeshRenderer.h"
extern lu::Application application;
namespace lu::JSAB
{
	void TutorialBeatBar::Initialize()
	{
		Vector3 baseScale = { 20, (float)application.GetHeight() * 2, 1 };
		Owner()->SetName(L"BeatBar");
		mTransform->SetPosition(Vector3::Up * (float)application.GetHeight() * 0.5);
		mTransform->SetScale(baseScale);

		mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"verticlebar"));
		mMr->GetMaterial()->SetTint(Color::clear);
		mMr->SetColor(Color::white)->UseColor(false);
	}
	void TutorialBeatBar::OnActivate()
	{
	}
	void TutorialBeatBar::OnDeActivate()
	{
	}
	void TutorialBeatBar::WhileActive()
	{
	}
	void TutorialBeatBar::WhileDeActive()
	{
	}
}