#pragma once
#include "..\\Engine_SOURCE\\LScript.h"
#include "..\\Engine_SOURCE\\LTransform.h"
namespace gui
{
	class TransformWidget : public lu::Script
	{
	public:
		TransformWidget();
		~TransformWidget();

		virtual void Initialize() override;
		virtual void Update() override;

	private:
		lu::Transform* mTransform;
	};
}

