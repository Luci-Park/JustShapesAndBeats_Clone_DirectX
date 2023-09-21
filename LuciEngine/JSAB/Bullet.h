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
#include "CameraScript.h"

namespace lu::JSAB
{
	class Bullet : public Script
	{
	public:
		enum class eBulletState { Waiting, Warning, Activate, Outro, DeActivate};
		Bullet() {};
		virtual ~Bullet() {};
		virtual void Initialize() override;
		virtual void Update() override;
		void SetTimeline(MusicController* music, double wt, double at, double ot);
		eBulletState GetBulletState() { return mBulletState; }
		void Warning();
		void Activate();
		void Outro();
		void DeActivate();
		void TestTime(double time);

	protected:
		void TimeCheck(double time);
		virtual void BulletSetUp() = 0;

		virtual void OnWarning() = 0;
		virtual void WhileWarning(double time) = 0;
		virtual void OnActivate() = 0;
		virtual void WhileActivate(double time) = 0;
		virtual void OnOutro() = 0;
		virtual void WhileOutro(double time) = 0;
		virtual void OnDeActivate() = 0;

		Vector2 PathInCircle(double durationforacircle, double time, float radius);

	private:
		void CheckState(double time);
		void ChangeToWarning(double time);
		void ChangeToActive(double time);
		void ChangeToOutro(double time);
	protected:
		CameraEffectScript* mCamera;
		eBulletState mBulletState;
		MusicController* mMusic;
		RECT mBounds;
		double mWarningTime;
		double mActivateTime;
		double mOutroTime;
		float mWarningProcess;
		float mActivateProcess;
		float mOutroProcess;
	};
}

