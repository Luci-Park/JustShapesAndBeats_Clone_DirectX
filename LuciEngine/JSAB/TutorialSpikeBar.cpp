//#include "TutorialEightBar.h"
//#include "TutorialEightBullets.h"
//#include "LObject.h"
//#include "LGameObject.h"
//#include "LTime.h"
//namespace lu::JSAB
//{
//	void TutorialHalfBar::Initialize()
//	{
//		Script::Initialize();
//		for (int i = 0; i < 10; i++)
//		{
//			mBullets[i] = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TutorialRoundSpikes>();
//			mBullets[i]->mTransform->SetLocalPosition({ 0, -200.f + 40.f * i, 0 });
//		}
//		Bullet::Initialize();
//	}
//	void TutorialHalfBar::Setup(float duration, Vector3 startPos, Vector3 endPos)
//	{
//		mDuration = duration;
//		mStartPos = startPos;
//		mEndPos = endPos;
//		mTime = 0;
//		mbIsMoving = mStartPos != mEndPos;
//	}
//	void TutorialHalfBar::OnActivate()
//	{
//		for (int i = 0; i < 10; i++)
//			mBullets[i]->Activate();
//	}
//	void TutorialHalfBar::OnDeActivate()
//	{
//		for (int i = 0; i < 10; i++)
//			mBullets[i]->DeActivate();
//	}
//	void TutorialHalfBar::WhileActive()
//	{
//		if (!mbIsMoving) return;
//		mTime += Time::DeltaTime();
//		float t = mTime / mDuration;
//		if (t <= 1.0f)
//		{
//			Vector3 pos = Vector3::Lerp(mStartPos, mEndPos, t);
//			mTransform->SetLocalPosition(pos);
//		}
//		else
//			DeActivate();
//	}
//	void TutorialFullBar::Initialize()
//	{
//		Script::Initialize();
//		mHalf[0] = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TutorialHalfBar>();
//		mHalf[0]->mTransform->SetLocalPosition({0, 200, 1});
//		mHalf[1] = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TutorialHalfBar>();
//		mHalf[1]->mTransform->SetLocalPosition({ 0, -200, 1 });
//		Bullet::Initialize();
//	}
//	void TutorialFullBar::Setup(float duration, Vector3 startPos, Vector3 endPos)
//	{
//		mDuration = duration;
//		mStartPos = startPos;
//		mEndPos = endPos;
//		mTime = 0;
//		mbIsMoving = mStartPos != mEndPos;
//		mTransform->SetPosition(mStartPos);
//	}
//	void TutorialFullBar::OnActivate()
//	{
//		mHalf[0]->Activate();
//		mHalf[1]->Activate();
//	}
//	void TutorialFullBar::OnDeActivate()
//	{
//		mHalf[0]->DeActivate();
//		mHalf[1]->DeActivate();
//	}
//	void TutorialFullBar::WhileActive()
//	{
//		if (!mbIsMoving) return;
//		mTime += Time::DeltaTime();
//		float t = mTime / mDuration;
//		if (t <= 1.0f)
//		{
//			Vector3 pos = Vector3::Lerp(mStartPos, mEndPos, t);
//			mTransform->SetLocalPosition(pos);
//		}
//		else
//			DeActivate();
//	}
//}