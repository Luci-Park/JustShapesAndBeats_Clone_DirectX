#pragma once
#include "Bullet.h"

namespace lu::JSAB
{
	class TutorialGiantCircle : public Bullet
	{
	public:
		TutorialGiantCircle();
		~TutorialGiantCircle();

	protected:
		virtual void BulletSetUp()override;
		virtual void OnWarning()override;
		virtual void WhileWarning(double time)override;
		virtual void OnActivate()override;
		virtual void WhileActivate(double time)override;
		virtual void OnOutro()override;
		virtual void WhileOutro(double time)override;
		virtual void OnDeActivate()override;

		void CreateAnimation();
	private:
		Animator* mAnim;
		MeshRenderer* mMr;
		Collider2D* mCol;
		double mTime;
	};
}

