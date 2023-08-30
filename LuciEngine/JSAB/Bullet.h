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
		Bullet():isActive(false) {};
		virtual ~Bullet() {};
		virtual void Initialize() override;
		virtual void Update() override;
		void Show();
		void Activate();
		void DeActivate();
		bool IsActive() { return isActive; }
	protected:
		virtual void OnShow() = 0;
		virtual void OnActivate() = 0;
		virtual void OnDeActivate() = 0;
		virtual void WhileActive() = 0;
		virtual void WhileDeActive() = 0;

	protected:
		bool isActive;

	};
}

