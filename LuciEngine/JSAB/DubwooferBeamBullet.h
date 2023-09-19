#pragma once
#include "Bullet.h"
namespace lu::JSAB
{
	class DubwooferBeamBullet : public Bullet
	{
	public:
		DubwooferBeamBullet():mSize(20){}
		virtual ~DubwooferBeamBullet(){}
		void SetRandom();
		void SetSize(float size) { mSize = size; }
	private:
		virtual void BulletSetUp()override;
		virtual void OnWarning()override;
		virtual void WhileWarning(double time)override;
		virtual void OnActivate()override;
		virtual void WhileActivate(double time)override;
		virtual void OnOutro()override;
		virtual void WhileOutro(double time)override;
		virtual void OnDeActivate()override;

		void CreateOnBeatAnimation();
		void CameraShake();

	private:
		MeshRenderer* mMr;
		Collider2D* mCol;
		Animator* mAnim;
		float mSize;
	};
}

