#pragma once
#include "Bullet.h"

namespace lu::JSAB
{
	class TutorialBeatCircle : public Bullet
	{
	public:
		TutorialBeatCircle() {}
		virtual ~TutorialBeatCircle() {}
		void FastAnim(bool fast) { mbFastActivate = fast; }
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
	private:
		MeshRenderer* mMr;
		Collider2D* mCol;
		Animator* mAnim;
		std::shared_ptr<Texture> mReadySprite;
		std::shared_ptr<Texture> mActivateSprite;
		bool mbFastActivate;
	};
	/*
	class TutorialCircleLine : public Bullet
	{
	public:
		TutorialCircleLine() {}
		virtual ~TutorialCircleLine() {}
		virtual void Initialize()override;

		void FitToWidth();
		void FitToHeight();

		void MultipleShow(const double* times);
	private:
		virtual void OnShow() override;
		virtual void OnActivate()override;
		virtual void OnDeActivate()override;
		virtual void WhileShowing() override;
		virtual void WhileActive()override;
		virtual void WhileDeActive()override;
	private:
		TutorialBeatCircle* mCircleLines[7];
	};*/
}

