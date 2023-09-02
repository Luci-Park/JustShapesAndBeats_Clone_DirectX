#pragma once
#include "LScript.h"

namespace lu
{
	class Animator;
	class Animation;
	class MeshRenderer;
	class Collider2D;
}

namespace lu::JSAB
{
	class Bullet : public Script
	{
	public:
		enum class BulletState
		{
			InActive, Show, Active
		};
		Bullet():mState(BulletState::InActive) {};
		virtual ~Bullet() {};
		virtual void Initialize() override;
		virtual void Update() override;
		void Show(double activateTime);
		void Activate();
		void DeActivate();
		bool IsActive() { return mState == BulletState::Active; }
		bool IsShow() { return mState == BulletState::Show; }
	protected:
		virtual void OnShow() = 0;
		virtual void OnActivate() = 0;
		virtual void OnDeActivate() = 0;
		virtual void WhileShowing() = 0;
		virtual void WhileActive() = 0;
		virtual void WhileDeActive() = 0;

	protected:
		BulletState mState;
		double mActivateTime;

	};
}

