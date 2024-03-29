#pragma once
#include "..\\Engine_SOURCE\\LScript.h"
#include "..\\Engine_SOURCE\\LGameObject.h"
#include "..\\Engine_SOURCE\\LTransform.h"
#include "..\\Engine_SOURCE\\LAnimator.h"
#include "..\\Engine_SOURCE\\LMeshRenderer.h"
#include "..\\Engine_SOURCE\\LCollider2D.h"
#include "..\\Engine_SOURCE\\LObject.h"
#include "..\\Engine_SOURCE\\LResources.h"
#include "MusicController.h"
#include "CameraScript.h"

namespace lu::JSAB
{
	class Bullet : public Script
	{
	public:
		enum class eBulletState { Waiting, Warning, Activate, Outro, DeActivate};
		Bullet() {}
		virtual ~Bullet() {}
		virtual void Initialize() override;
		virtual void Update() override;
		void SetTimeline(MusicController* music, double wt, double at, double ot);
		eBulletState GetBulletState() { return mBulletState; }
		void Warning();
		void Activate();
		void Outro();
		void DeActivate();
		void TestTime(double time);
		bool IsDeActivatable();

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

