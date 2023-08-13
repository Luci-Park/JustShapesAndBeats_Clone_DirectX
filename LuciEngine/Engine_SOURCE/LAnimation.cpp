#include "LAnimation.h"

namespace lu
{
	Animation::Animation()
		:Resource(enums::eResourceType::Animation)
	{
	}
	Animation::~Animation()
	{
	}
	void Animation::Update()
	{
	}
	void Animation::LateUpdate()
	{
	}
	void Animation::Render()
	{
	}
	void Animation::Reset()
	{
		mTime = 0.0f;
		mbComplete = false;
	}
}