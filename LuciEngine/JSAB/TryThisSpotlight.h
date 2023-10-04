#pragma once
#include "Bullet.h"
namespace lu::JSAB
{
	class TryThisSpotlight : public Bullet
	{
	public:
		TryThisSpotlight(){}
		virtual ~TryThisSpotlight(){}

	private:
		virtual void BulletSetUp() override;

		virtual void OnWarning() override;
		virtual void WhileWarning(double time) override;
		virtual void OnActivate() override;
		virtual void WhileActivate(double time) override;
		virtual void OnOutro()override;
		virtual void WhileOutro(double time) override;
		virtual void OnDeActivate() override;

	private:
		Animator* mAnim;
		std::shared_ptr<Texture> mReadySprite;
		std::shared_ptr<Texture> mActivateSprite;
		std::shared_ptr<Texture> mOutlineSprite;
		GameObject* mWarning;
	};
}

