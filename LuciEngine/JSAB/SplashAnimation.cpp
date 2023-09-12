#include "SplashAnimation.h"
#include "LObject.h"
#include "LGameObject.h"
#include "LAnimator.h"
#include "OpeningUIObjects.h"

namespace lu::JSAB::Title
{
	void SplashAnimation::Initialize()
	{
		mAnim = Owner()->AddComponent<Animator>();
		mShapes = object::Instantiate<ShapesObject>(eLayerType::UI)->GetComponent<Animator>();
		mAnd = object::Instantiate<AndObject>(eLayerType::UI)->GetComponent<Animator>();
		mBeats = object::Instantiate<BeatsObject>(eLayerType::UI)->GetComponent<Animator>();

		auto a = mAnim->CreateAnimation(L"Fade In");
		a->AddFunctionKey(0, std::bind(&Animator::PlayAnimation, mShapes, L"Fade In", false));
		a->AddFunctionKey(0.3, std::bind(&Animator::PlayAnimation, mAnd, L"Fade In", false));
		a->AddFunctionKey(0.6, std::bind(&Animator::PlayAnimation, mBeats, L"Fade In", false));
		
		mAnim->PlayAnimation(L"Fade In", true);
	}
}