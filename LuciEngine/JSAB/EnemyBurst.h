#pragma once
#include "Enemy.h"
namespace lu::JSAB
{
	class EnemyBurst : public Enemy
	{
	public:
		EnemyBurst():mRotateSpeed(-2*PI), mParticleMoveSpeed(300) {}
		virtual ~EnemyBurst() {}

		void SetPosition(Vector3 start, Vector3 end) { mStartPos = start; mEndPos = end; }
	protected:
		virtual void BulletSetUp() override;
		virtual void OnWarning() override;
		virtual void WhileWarning(double time) override;
		virtual void OnActivate()override;
		virtual void WhileActivate(double time) override;
		virtual void OnOutro()override {}
		virtual void WhileOutro(double time)override {}
		virtual void OnDeActivate() override;
	private:
		void CreateAnimation();
		void CreateMoveAnimation(Animation* ani, Vector3 startPos, Vector3 endPos, double duration);
	private:
		Transform* mShell;
		Transform* mBursts[8];
		Vector3 mParticleDirection[8];

		Vector3 mStartPos;
		Vector3 mEndPos;

		float mRotateSpeed;
		float mParticleMoveSpeed;

	};
}

