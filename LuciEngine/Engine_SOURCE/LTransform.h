#pragma once
#include "LComponent.h"

namespace lu
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindConstantBuffer();

		void SetPosition(Vector3 position) { mPosition = position; CalculateLocalPosition(); }
		void SetRotation(Quaternion rotation) { mRotation = rotation; CalculateLocalRotation(); }
		void SetScale(Vector3 scale) { mScale = scale; CalculateLocalScale(); }

		void SetPosition(float x, float y, float z) { mPosition = Vector3(x, y, z); }
		void SetRotation(float x, float y, float z) { mRotation = Quaternion::CreateFromYawPitchRoll(Vector3(x, y, z)); }
		void SetScale(float x, float y, float z) { mScale = Vector3(x, y, z); }

		void SetLocalPosition(Vector3 position) { mLocalPosition = position; CalculateWorldPosition(); }
		void SetLocalRotation(Quaternion rotation) { mLocalRotation = rotation; CalculateWorldRotation(); }
		void SetLocalScale(Vector3 scale) { mLocalScale = scale; CalculateWorldScale(); }

		Vector3 GetPosition() { return mPosition; }
		Quaternion GetRotation() { return mRotation; }
		Vector3 GetScale() { return mScale; }

		Vector3 GetLocalPosition() { return mLocalPosition; }
		Quaternion GetLocalRotation() { return mLocalRotation; }
		Vector3 GetLocalScale() { return mLocalScale; }

		Vector3 Forward() { return mForward; }
		Vector3 Right() { return mRight; }
		Vector3 Up() { return mUp; }

		void SetParent(Transform* parent);
		Transform* GetParent() { return mParent; }

		void AddChildren(Transform* child);
		const std::vector<Transform*>& GetChildren() { return mChildren; }

		void RemoveChildren(Transform* child);

		Matrix& GetMatrix() { return world; }
	private:
		void CalculateWorldPosition();
		void CalculateWorldRotation();
		void CalculateWorldScale();

		void CalculateLocalPosition();
		void CalculateLocalRotation();
		void CalculateLocalScale();

		void UpdateMatrix();
	private:
		Vector3 mPosition;
		Quaternion mRotation;
		Vector3 mScale;

		Vector3 mLocalPosition;
		Quaternion mLocalRotation;
		Vector3 mLocalScale;

		Vector3 mUp;
		Vector3 mForward;
		Vector3 mRight;

		Matrix world;
		Transform* mParent;
		std::vector<Transform*> mChildren;
	};
}
