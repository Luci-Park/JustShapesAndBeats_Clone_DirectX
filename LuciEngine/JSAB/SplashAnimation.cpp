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
		object::Instantiate<ShapesObject>(eLayerType::UI);
		object::Instantiate<AndObject>(eLayerType::UI);
		object::Instantiate<BeatsObject>(eLayerType::UI);
	}
}