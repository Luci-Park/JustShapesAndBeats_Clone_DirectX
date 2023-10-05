#pragma once
#include "Bullet.h"
namespace lu::JSAB
{
	class TryThisSpotlight : public Bullet
	{
	public:
		TryThisSpotlight() {}
		virtual ~TryThisSpotlight() {}
	private:
		virtual void BulletSetUp()override;
		virtual void OnWarning()override;
		virtual void WhileWarning(double time)override;
		virtual void OnActivate()override;
		virtual void WhileActivate(double time)override;
		virtual void OnOutro()override;
		virtual void WhileOutro(double time)override;
		virtual void OnDeActivate()override;
	private:
		MeshRenderer* mFillMr;
		Transform* mFillTr;
		Animator* mFillAnim;

	};
}

