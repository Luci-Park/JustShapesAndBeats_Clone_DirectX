#pragma once
#include "LComponent.h"
namespace lu
{
	class Script : public Component
	{
	public:
		Script();
		virtual ~Script();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
	};
}

