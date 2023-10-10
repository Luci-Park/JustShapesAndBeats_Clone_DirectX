#pragma once
#include "Bullet.h"
namespace lu::JSAB
{
	class TryThisSpotlight : public Bullet
	{
	public:
		TryThisSpotlight() {}
		virtual ~TryThisSpotlight() {}
		virtual void Update();
		void RotateClockWise() { mRotSpeed = -1; }
		void RotateCounterClockWise() { mRotSpeed = 1; }
		void SetCenter(Vector3 pos);
		void SetStartAngle(float degrees);
		void Flash(bool flash) { mbFlashWhite = flash; }
		void FadeIn();
	private:
		virtual void BulletSetUp()override;
		virtual void OnWarning()override;
		virtual void WhileWarning(double time)override;
		virtual void OnActivate()override;
		virtual void WhileActivate(double time)override;
		virtual void OnOutro()override;
		virtual void WhileOutro(double time)override;
		virtual void OnDeActivate()override;

		void Move();
		void Rotate();
	private:
		MeshRenderer* mMr;
		Animator* mAnim;
		
		MeshRenderer* mFillMr;
		Transform* mFillTr;
		Animator* mFillAnim;
		Collider2D* mFillCol;

		float mRotSpeed;
		float mAngle;
		Vector3 mMoveCenter;
		bool mbFlashWhite;
	};
}

