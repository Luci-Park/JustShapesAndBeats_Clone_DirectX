#include "TutorialEightBulletScript.h"
#include "MusicController.h"
#include "LGameObject.h"
namespace lu::JSAB
{
	void MoveFoward::Initialize()
	{
		mTr = Owner()->mTransform;
	}
	void MoveFoward::Update()
	{
		double time = MusicController::_MusicController->GetTime();
		float endTime = mStartTime + mDuration;
		float t = (time - mStartTime) / (endTime - mStartTime);
		Vector3 pos = Vector3::Lerp(mStartPos, mEndPos, t);
		mTr->SetLocalPosition(pos);
		if (t >= 1.f)
			Owner()->SetActive(false);
	}
}
