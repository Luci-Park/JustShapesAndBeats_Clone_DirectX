#pragma once
#include "Bullet.h"

namespace lu::JSAB
{
	class TutorialGiantCircle : public Bullet
	{
	public:
		TutorialGiantCircle();
		~TutorialGiantCircle();

		virtual void Initialize() override;

	protected:
		virtual void OnShow() = 0;
		virtual void OnActivate() = 0;
		virtual void OnDeActivate() = 0;
		virtual void WhileShowing() = 0;
		virtual void WhileActive() = 0;
		virtual void WhileDeActive() = 0;
	private:
	};
}

