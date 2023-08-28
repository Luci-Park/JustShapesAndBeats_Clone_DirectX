#pragma once
#include "LScript.h"

namespace lu
{
	class Transform;
}

namespace lu::JSAB
{
	class Bullet : public Script
	{
	public:
		virtual void Update();
		void Activate();
		void DeActivate();

	protected:
		virtual void OnActivate() = 0;
		virtual void OnDeActivate() = 0;
		virtual void WhileActive() = 0;
		virtual void WhileDeActive() = 0;

	protected:
		Transform* mTr;
		bool isActive;

	};
}

