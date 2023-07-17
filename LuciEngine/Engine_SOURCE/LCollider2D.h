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

		void OnCollisionEnter(Collider2D* other);
		void OnCollisionStay(Collider2D* other);
		void OnCollisionExit(Collider2D* other);

		void SetType(eColliderType type) { mType = type; }
		void SetSize(Vector2 size) { mSize = size; }
		void SetCenter(Vector2 size) { mCenter = size; }

		UINT GetColliderID() { return mColliderID; }

		eColliderType GetType() { return mType; }
		Vector2 GetSize() { return mSize; }
		Vector2 GetCenter() { return mCenter; }
		Vector3 GetRotation() { return mRotation; }
	private:
		static UINT mColliderNumber;
		UINT mColliderID;
		eColliderType mType;
		Transform* mTransform;

		Vector3 mPosition;
		Vector2 mSize;
		Vector2 mCenter;
		Vector3 mRotation;
	};
}

