#include "CheckPoint.h"
#include "LApplication.h"
#include "MusicManager.h"
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

		float x = mMr->GetMaterial()->GetTexture()->GetRatioWidth(720);
		mTransform->SetScale(x, 720, 1);

		mCol = Owner()->AddComponent<Collider2D>();

		mAudio = Owner()->AddComponent<AudioSource>();
		mAudio->SetClip(Resources::Find<AudioClip>(L"SFX_POWERUP_2"));
		mAudio->SetLoop(false);
	}
	void CheckPoint::OnWarning()
	{
		mMr->SetActive(true);
		mCol->SetActive(true);
		mTransform->SetPosition({ (float)mBounds.right, 0, -3});
	}
	void CheckPoint::WhileWarning(double time)
	{
		if (mWarningProcess > 0.5)
			int i = 0;
		Vector3 pos = Vector3::Lerp({ (float)mBounds.right, 0, -3 }, { (float)mBounds.left, 0, -3 }, mWarningProcess);
		mTransform->SetPosition(pos);
		if (pos.x == (float)mBounds.left)
			DeActivate();
	}
	void CheckPoint::OnDeActivate()
	{
		mTransform->SetPosition({ (float)mBounds.right, 0, -3 });
		mMr->SetActive(false);
		mCol->SetActive(false);
	}
}