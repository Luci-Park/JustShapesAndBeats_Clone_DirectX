#include "CheckPoint.h"
#include "LApplication.h"

extern lu::Application application;
namespace lu::JSAB
{
	void CheckPoint::OnCollisionEnter(Collider2D* other)
	{
		if (other->Owner()->GetLayer() == eLayerType::Player)
		{
			mAudio->Play();
			DeActivate();
			mBackground->SetBackground(mChange);
		}
	}
	void CheckPoint::BulletSetUp()
	{
		Owner()->SetTag(eTagType::Item);

		mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))
			->SetMaterial(Resources::Load<Material>(L"CheckPointMat", L"CheckPointLine"));
		mMr->GetMaterial()->SetRenderingMode(eRenderingMode::CutOut);

		float x = mMr->GetMaterial()->GetTexture()->GetRatioWidth(application.GetHeight());
		mTransform->SetScale(x, application.GetHeight(), 0);

		mStartPos = { application.GetWidth() * 0.5f + x, 0, -3 };
		mEndPos = { application.GetWidth() * -0.5f - x, 0, -3 };
		
		mCol = Owner()->AddComponent<Collider2D>();

		mAudio = Owner()->AddComponent<AudioSource>();
		mAudio->SetClip(Resources::Find<AudioClip>(L"SFX_POWERUP_2"));
		mAudio->SetLoop(false);
	}
	void CheckPoint::OnWarning()
	{
		mMr->SetActive(true);
		mCol->SetActive(true);
		mTransform->SetPosition(mStartPos);
	}
	void CheckPoint::WhileWarning(double time)
	{
		Vector3 pos = Vector3::Lerp(mStartPos, mEndPos, mWarningProcess);
		mTransform->SetPosition(pos);
		if (pos == mEndPos)
			DeActivate();
	}
	void CheckPoint::OnDeActivate()
	{
		mTransform->SetPosition(mStartPos);
		Owner()->SetActive(false);
	}
}