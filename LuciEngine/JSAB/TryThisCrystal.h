#pragma once
#include "Bullet.h"
namespace lu::JSAB
{
	class TryThisCrystal : public Script
	{
	public:
		TryThisCrystal() {}
		virtual ~TryThisCrystal() {}
		virtual void Initialize();
		virtual void Update();
		void Activate();
	private:
		bool mbMove;

	};
}

