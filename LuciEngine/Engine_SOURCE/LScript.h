#pragma once
#include "LComponent.h"
namespace lu
{
	class Transform;
	class Collider2D;
	class Script : public Component
	{
	public:
		Script();
		virtual ~Script();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other) {}
		virtual void OnCollisionStay(Collider2D* other) {}
		virtual void OnCollisionExit(Collider2D* other) {}

		virtual void OnEnable() {}
		virtual void OnDisable() {}

		virtual void SetState(eState state) override;

	public:
		Transform* mTransform;
		
	};
}

