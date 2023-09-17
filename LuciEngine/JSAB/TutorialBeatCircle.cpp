#include "TutorialBeatCircle.h"
#include "GeneralEffects.h"
#include "LSceneManager.h"
#include "LApplication.h"

extern lu::Application application;
namespace lu::JSAB
{
#pragma region TutorialBeatCircle
	void TutorialBeatCircle::BulletSetUp()
	{
		Owner()->SetName(L"BeatCircle");
		mTransform->SetLocalScale({ 230, 230, 1 });
		mCol = Owner()->AddComponent<Collider2D>()->SetType(eColliderType::Circle);

		mMr = Owner()->AddComponent<MeshRenderer>();
		mMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"))->SetMaterial(GetGeneralMaterial(L"circle_bullet_prep"));
		mMr->SetColor(Color::white)->UseColor(false);

		mReadySprite = Resources::Find<Texture>(L"circle_bullet_prep");
		mActivateSprite = Resources::Find<Texture>(L"circle_bullet");

		mAnim = Owner()->AddComponent<Animator>();
		CreateOnBeatAnimation();
	}
	void TutorialBeatCircle::OnWarning()
	{
		mMr->SetActive(true);
		mAnim->SetActive(true);
		mAnim->PlayAnimation(L"Preparation", true);
	}
	void TutorialBeatCircle::WhileWarning(double time)
	{
	}

	void TutorialBeatCircle::OnActivate()
	{
		mMr->SetActive(true);
		mAnim->SetActive(true);
		if(mbFastActivate)
			mAnim->PlayAnimation(L"FastActivate", false);
		else
			mAnim->PlayAnimation(L"SlowActivate", false);
	}
	void TutorialBeatCircle::WhileActivate(double time)
	{
	}
	void TutorialBeatCircle::OnOutro()
	{
	}
	void TutorialBeatCircle::WhileOutro(double time)
	{
	}
	void TutorialBeatCircle::OnDeActivate()
	{
		mCol->SetActive(false);
		mMr->SetActive(false);
		mAnim->SetActive(false);
		mTransform->SetLocalScale({ 230, 230, 1 });
	}

	void TutorialBeatCircle::CreateOnBeatAnimation()
	{
		Animation* anim = mAnim->CreateAnimation(L"Preparation");
		anim->AddTextureKey(0, mReadySprite);
		CreateCounterClockwiseAnimation(0.5, anim);

		{
			double duration = 0.3;
			anim = mAnim->CreateAnimation(L"FastActivate");
			anim->AddTextureKey(0, mActivateSprite);
			anim->AddColliderActiveKey(0, true);

			anim->AddInterpolationKey(0, 0);
			anim->AddInterpolationKey(duration * 0.5, 0.5);
			anim->AddInterpolationKey(duration * 0.6, 0.8);
			anim->AddInterpolationKey(duration, 0);

			anim->AddScaleKey(0, { 230, 230, 1 });
			anim->AddScaleKey(duration * 0.5, { 280, 280, 1 });
			anim->AddScaleKey(duration * 0.6, { 300, 300, 1 });
			anim->AddScaleKey(duration, { 0, 0 , 1 });

			anim->AddFunctionKey(duration, std::bind(&Bullet::DeActivate, this));
		}
		{
			Animation* anim = mAnim->CreateAnimation(L"SlowActivate");
			double duration = 0.6;
			anim->AddTextureKey(0, mActivateSprite);
			anim->AddColliderActiveKey(0, true);

			anim->AddInterpolationKey(0, 0);
			anim->AddInterpolationKey(duration * 0.3, 0.5);
			anim->AddInterpolationKey(duration * 0.6, 0.8);
			anim->AddInterpolationKey(duration, 0);

			anim->AddLocalScaleKey(0, { 100, 100, 1 });
			anim->AddLocalScaleKey(duration * 0.3, { 280, 280, 1 });
			anim->AddLocalScaleKey(duration * 0.9, { 300, 300, 1 });
			anim->AddLocalScaleKey(duration, { 0, 0 , 1 });

			anim->AddFunctionKey(duration, std::bind(&Bullet::DeActivate, this));
		}
	}
#pragma endregion


#pragma region TutorialCircleLine
	//void TutorialCircleLine::Initialize()
	//{
	//	Script::Initialize();
	//	for (int i = 0; i < 7; i++)
	//	{
	//		auto b = object::Instantiate<GameObject>(mTransform, eLayerType::Bullet)->AddComponent<TutorialBeatCircle>();
	//		b->mTransform->SetLocalPosition({ -690.f + 230.f * i, 0, 0 });
	//		mCircleLines[i] = b;
	//	}
	//	
	//}
	//void TutorialCircleLine::FitToWidth()
	//{
	//	const float width = 1610.f;
	//	const float target = 1000.f;
	//	mTransform->SetScale({ target / width, target / width, 1 });
	//	Vector3 scale = { target / width * 300, target / width * 300, 1 };
	//	float startPos = 0 - scale.x * 3;
	//	for (int i = 0; i < 7; i++)
	//	{
	//		mCircleLines[i]->mTransform->SetLocalPosition({ startPos + scale.x * i, 0, 0 });
	//		mCircleLines[i]->FastAnim(false);
	//	}
	//}
	//void TutorialCircleLine::FitToHeight()
	//{
	//	const float width = 1610.f;
	//	const float target = 800.f;
	//	mTransform->SetScale({ target / width, target / width, 1 });
	//	Vector3 scale = { target / width * 200, target / width * 200, 1 };
	//	float startPos = 0 + scale.x * 3;
	//	for (int i = 0; i < 7; i++)
	//	{
	//		mCircleLines[i]->mTransform->SetLocalPosition({ 0, startPos - scale.x * i, 0 });
	//	}
	//	mTransform->SetPosition({ RealRandom(application.GetWidth() * -0.5f + scale.x, application.GetWidth() * 0.5f - scale.x), 0, 0 });
	//}
	//void TutorialCircleLine::MultipleShow(const double* times)
	//{
	//	for (int i = 0; i < 7; i++)
	//		mCircleLines[i]->Show(times[i]);
	//}
	//void TutorialCircleLine::OnShow()
	//{
	//	for (int i = 0; i < 7; i++)
	//		mCircleLines[i]->Show(mActivateTime);
	//}
	//void TutorialCircleLine::OnActivate()
	//{
	//	for (int i = 0; i < 7; i++)
	//		mCircleLines[i]->Activate();
	//}
	//void TutorialCircleLine::OnDeActivate()
	//{
	//	for (int i = 0; i < 7; i++)
	//		mCircleLines[i]->DeActivate();
	//}
	//void TutorialCircleLine::WhileShowing()
	//{
	//}
	//void TutorialCircleLine::WhileActive()
	//{
	//}
	//void TutorialCircleLine::WhileDeActive()
	//{
	//}
#pragma endregion

}