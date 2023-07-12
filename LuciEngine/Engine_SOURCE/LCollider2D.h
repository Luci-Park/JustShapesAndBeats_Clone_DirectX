#pragma once
#include "LComponent.h"
#include "LTransform.h"

namespace lu
{
	class Collider2D : public Component
	{
	public:
		Collider2D();
		~Collider2D();
		
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetType(eColliderType type) { mType = type; }

	private:
		eColliderType mType;
		Transform* mTransform;
		Vector2 mSize;
		Vector2 mCenter;
	};
}

