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

		void SetPosition(Vector3 position);
		void SetRotation(Quaternion rotation);
		void SetScale(Vector3 scale);

		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void SetScale(float x, float y, float z);

		void SetLocalPosition(Vector3 position);
		void SetLocalRotation(Quaternion rotation);
		void SetLocalScale(Vector3 scale);

		void SetLocalPosition(float x, float y, float z);
		void SetLocalRotation(float x, float y, float z);
		void SetLocalScale(float x, float y, float z);

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

		Matrix& GetMatrix() { return mTransformMatrix; }
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

		Matrix mTransformMatrix;
		Transform* mParent;
		std::vector<Transform*> mChildren;
	};
}
