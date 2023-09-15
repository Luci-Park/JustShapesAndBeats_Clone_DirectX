#pragma once
#include "LScript.h"
#include "MusicController.h"
#include "LGameObject.h"
#include "LTransform.h"
#include "LAnimator.h"
#include "LMeshRenderer.h"
#include "LCollider2D.h"
#include "LObject.h"
#include "LResources.h"

namespace lu::JSAB
{
	class CameraEffectScript;
	class Enemy : public Script
	{
	public:
		enum class eState{DeActivate, Warning, Activate, Outro};
		Enemy() {};
		virtual ~Enemy() {};
		virtual void Initialize() override;
		virtual void Update() override;
		void SetTimeline(MusicController* music, double wt, double at, double ot);
		void DeActivate();

	protected:
		virtual void BulletSetUp() = 0;

		virtual void OnWarning() = 0;
		virtual void WhileWarning(double time) = 0;
		virtual void OnActivate() = 0;
		virtual void WhileActivate(double time) = 0;
		virtual void OnOutro() = 0;
		virtual void WhileOutro(double time) = 0;
		virtual void OnDeActivate() = 0;
	private:
		void CheckState(double time);
		void ChangeToWarning(double time);
		void ChangeToActive(double time);
		void ChangeToOutro(double time);
	protected:
		CameraEffectScript* mCamera;
		eState mState;
		MusicController* mMusic;
		double mWarningTime;
		double mActivateTime;
		double mOutroTime;
	};
}