#include "TutorialEightBulletScript.h"
#include "MusicController.h"
#include "LGameObject.h"
#include "LTime.h"
namespace lu::JSAB
{
	void MoveFoward::Initialize()
	{
		mTr = Owner()->mTransform;
	}
	void MoveFoward::Update()
	{
		mTime += Time::DeltaTime();
		float t = mTime / mDuration;
		if (t <= 1.0f)
		{
			Vector3 pos = Vector3::Lerp(mStartPos, mEndPos, t);
			mTr->SetLocalPosition(pos);
		}
		else
			Owner()->SetActive(false);
	}
}
