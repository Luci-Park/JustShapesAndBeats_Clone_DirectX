#pragma once
#pragma once
#include "..\\Engine_SOURCE\\LGameObject.h"
namespace gui
{
	class DebugObject : public lu::GameObject
	{
	public:
		DebugObject();
		virtual ~DebugObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}
