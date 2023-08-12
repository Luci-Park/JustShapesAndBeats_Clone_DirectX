#pragma once
#include "..\\Engine_SOURCE\\LScript.h"
namespace gui
{
	class TransformWidget : public lu::Script
	{
	public:
		TransformWidget();
		~TransformWidget();

		virtual void Update() override;

	private:
		float fMoveSpeed;
		float fRotateSpeed;
		float fScaleSpeed;
	};
}

