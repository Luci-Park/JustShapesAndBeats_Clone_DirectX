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

	class TutorialCircleLine : public Script
	{
	public:
		TutorialCircleLine(){}
		virtual ~TutorialCircleLine() {}
		virtual void Initialize() override;

		void Warning();
		void Activate();
		void DeActivate();
		void FitToWidth();
		void FitToHeight();

		void SetTimeline(MusicController* music, double wt, double at);
		void MultipleShow(MusicController* music, const double* wt, const double* at);

		bool IsDeActivatable();
	private:
		TutorialBeatCircle* mCircleLines[7];
	};
}

