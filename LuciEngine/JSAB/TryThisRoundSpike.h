#pragma once
#include "Bullet.h"
namespace lu::JSAB
{
	class TryThisRoundSpike : public Bullet
	{
	public:
		TryThisRoundSpike(){}
		virtual ~TryThisRoundSpike(){}

		void Setup(Vector3 dir, bool clockwise);
	private:
		virtual void BulletSetUp()override;
		virtual void OnWarning()override;
		virtual void WhileWarning(double time)override;
		virtual void OnActivate()override;
		virtual void WhileActivate(double time)override;
		virtual void OnOutro()override;
		virtual void WhileOutro(double time)override;
		virtual void OnDeActivate()override;

		void CreateEnterEffect();

	private:
		Animator* mEnterEffect;
		Collider2D* mCol;
		MeshRenderer* mMr;
		Vector3 mMoveDir;
		float mMoveSpeed;
		float mRotateSpeed;
	};

}

