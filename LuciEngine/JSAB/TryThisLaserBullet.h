#pragma once
#include "Bullet.h"

namespace lu::JSAB
{
	class TryThisLaserBase : public Script
	{
	public:
		TryThisLaserBase(){}
		virtual ~TryThisLaserBase(){}

		virtual void Initialize() override;
		void Ready();
		void SetAlpha(float alpha);
		void Activate();
	private:
		MeshRenderer* mMr;
		Animator* mAnim;
	};


	class TryThisLaserPart : public Script
	{
	public:
		TryThisLaserPart() {}
		virtual ~TryThisLaserPart() {}

		virtual void Initialize() override;
		void SetAlpha(float alpha);
		void Ready();
		void Activate();
		void DeActivate();
	private:
		MeshRenderer* mMr;
		Animator* mAnim;
		Collider2D* mCol;
	};
	
	
	class TryThisLaserBullet : public Bullet
	{
	public:
		TryThisLaserBullet() {}
		virtual ~TryThisLaserBullet() {}
		virtual void Update() override;
		void RotateClockWise() { mRotSpeed = -0.1; }
		void RotateCounterClockWise() { mRotSpeed = 0.1; }
		void Shake();
		void SetOrg(Vector3 pos) { mOrgPos = pos; }
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
		TryThisLaserBase* mBase;
		TryThisLaserPart* mLaser1;
		TryThisLaserPart* mLaser2;
		Animator* mAnim;
		float mRotSpeed;
		bool mbShake;
		Vector3 mOrgPos;
	};
}

