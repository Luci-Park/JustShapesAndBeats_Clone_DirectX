#include "LAnimator.h"
#include "LAnimation.h"

namespace lu
{
	Animator::Animator()
		:Component(eComponentType::Animator)
	{
	}
	Animator::~Animator()
	{
		for (auto& it : mAnimations)
		{
			delete it.second;
			it.second = nullptr;
		}
	}
	void Animator::Initialize()
	{
	}
	void Animator::Update()
	{
		if (mActiveAnimation == nullptr)
			return;
		if (mActiveAnimation->IsComplete() && mbLoop)
		{
			mActiveAnimation->Reset();
		}
	}
	void Animator::LateUpdate()
	{
		if(mActiveAnimation)
			mActiveAnimation->LateUpdate();
	}
	void Animator::Render()
	{
	}
	Animation* Animator::CreateAnimation(const std::wstring& name)
	{
		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
		{
			animation = new Animation(Owner());
			animation->SetKey(name);
			mAnimations.insert({ name, animation });
		}
		return animation;
	}
	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}
	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* prevAnimation = mActiveAnimation;
		Animation* animation = FindAnimation(name);
		if (animation)
		{
			mActiveAnimation = animation;
		}
		mbLoop = loop;
		mActiveAnimation->Reset();
	}
}