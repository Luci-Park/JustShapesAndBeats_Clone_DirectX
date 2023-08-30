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
		virtual void OnShow() override;
		virtual void OnActivate()override;
		virtual void OnDeActivate()override;
		virtual void WhileShowing() override;
		virtual void WhileActive()override;
		virtual void WhileDeActive()override;

		void CreateOnBeatAnimation();
	private:
		MeshRenderer* mMr;
		Collider2D* mCol;
		Animator* mAnim;
		std::shared_ptr<Texture> mReadySprite;
		std::shared_ptr<Texture> mActivateSprite;
	};
}

