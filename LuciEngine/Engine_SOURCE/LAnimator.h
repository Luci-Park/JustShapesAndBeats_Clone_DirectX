#pragma once
#include "LComponent.h"
#include "LAnimation.h"
namespace lu
{
	class Animator : public Component
	{
	public:
		Animator();
		virtual ~Animator();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		Animation* CreateAnimation(const std::wstring& name);
		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop);
	private:
		std::map<std::wstring, Animation*>mAnimations;
		Animation* mActiveAnimation;
		bool mbLoop;
	};
}

