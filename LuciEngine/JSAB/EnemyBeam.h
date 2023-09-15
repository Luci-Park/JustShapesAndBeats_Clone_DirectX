#pragma once
#include "Enemy.h"

namespace lu::JSAB
{
	class EnemyBeam : public Enemy
	{
	public:
		EnemyBeam() {};
		virtual ~EnemyBeam();

	private:
		virtual void BulletSetUp() override;

		virtual void OnDeActivate() override;
		virtual void OnWarning() override;
		virtual void WhileWarning(double time) override;
		virtual void OnActivate() override;
		virtual void WhileActivate(double time) override;
		virtual void OnOutro() override;
		virtual void WhileOutro(double time) override;

		void CreateOnBeatAnimation();
		void Beat();
	private:
		RECT boundary;
		MeshRenderer* mMr;
		Collider2D* mCol;
		Animator* mAnim;
	};
}
