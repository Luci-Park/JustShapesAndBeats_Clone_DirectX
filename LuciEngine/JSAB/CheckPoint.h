#pragma once
#include "Bullet.h"
#include "BackgroundScript.h"
namespace lu::JSAB
{
	class CheckPoint : public Bullet
	{
	public:
		CheckPoint(){}
		virtual ~CheckPoint(){}

		virtual void OnCollisionEnter(Collider2D* other) override;
		void SetBackgroundType(BackgroundScript::eBackgrounds type) { mChange = type; }
		void SetBackground(BackgroundScript* background) { mBackground = background; }
		void SetIsFinal(bool final) { mIsFinal = final; }
	protected:
		virtual void BulletSetUp() override;

		virtual void OnWarning() override;
		virtual void WhileWarning(double time) override;
		virtual void OnActivate() override {};
		virtual void WhileActivate(double time) override {};
		virtual void OnOutro() override {};
		virtual void WhileOutro(double time) override {};
		virtual void OnDeActivate() override;

	private:
		bool mIsFinal;

		MeshRenderer* mMr;
		Collider2D* mCol;
		AudioSource* mAudio;
		Vector3 mStartPos, mEndPos;
		BackgroundScript* mBackground;
		BackgroundScript::eBackgrounds mChange;
	};
}

