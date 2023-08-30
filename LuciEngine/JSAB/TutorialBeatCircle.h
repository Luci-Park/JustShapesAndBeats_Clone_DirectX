#pragma once
#include "Bullet.h"

namespace lu::JSAB
{
	class TutorialBeatCircle : public Bullet
	{
	public:
		TutorialBeatCircle() {}
		virtual ~TutorialBeatCircle() {}
		virtual void Initialize()override;
	private:
		virtual void OnShow();
		virtual void OnActivate();
		virtual void OnDeActivate();
		virtual void WhileActive();
		virtual void WhileDeActive();

		void CreateOnBeatAnimation();
	private:
		MeshRenderer* mMr;
		Collider2D* mCol;
		Animator* mAnim;
		std::shared_ptr<Texture> mReadySprite;
		std::shared_ptr<Texture> mActivateSprite;
	};
}

