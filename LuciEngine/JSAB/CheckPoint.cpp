#include "CheckPoint.h"
#include "LApplication.h"
#include "MusicManager.h"
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
			if (mIsFinal)
				mManager->OnMusicEnd();
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
		
		mCol = Owner()->AddComponent<Collider2D>();

		mAudio = Owner()->AddComponent<AudioSource>();
		mAudio->SetClip(Resources::Find<AudioClip>(L"SFX_POWERUP_2"));
		mAudio->SetLoop(false);
	}
	void CheckPoint::OnWarning()
	{
		mMr->SetActive(true);
		mCol->SetActive(true);
		mTransform->SetPosition({ (float)mBounds.right, 0, 0});
	}
	void CheckPoint::WhileWarning(double time)
	{
		Vector3 pos = Vector3::Lerp({ (float)mBounds.right, 0, 0 }, { (float)mBounds.left, 0, 0 }, mWarningProcess);
		mTransform->SetPosition(pos);
		if (pos.x == (float)mBounds.left)
			DeActivate();
	}
	void CheckPoint::OnDeActivate()
	{
		mTransform->SetPosition({ (float)mBounds.right, 0, 0 });
		mMr->SetActive(false);
		mCol->SetActive(false);
	}
}