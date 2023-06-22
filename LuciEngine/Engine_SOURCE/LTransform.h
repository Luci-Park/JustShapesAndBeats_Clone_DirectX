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

		void SetPos(Vector3 pos) { mWorldPos = pos; CalculateLocalPos(); }
		void SetRot(Vector3 rot) { mWorldRot = rot; CalculateLocalRot(); }
		void SetScale(Vector3 scale) { mWorldScale = scale; CalculateLocalScale(); }
		void SetLocalPos(Vector3 pos) { mLocalPos = pos; CalculateWorldPos(); }
		void SetLocalRot(Vector3 rot) { mLocalRot = rot; CalcluateWorldRot(); }
		void SetLocalScale(Vector3 scale) { mLocalScale = scale; CalculateWorldScale(); }

		Vector3 GetPos() { return mWorldPos; }
		Vector3 GetRot() { return mWorldRot; }
		Vector3 GetScale() { return mWorldScale; }
		Vector3 GetLocalPos() { return mLocalPos; }
		Vector3 GetLocalRot() { return mLocalRot; }
		Vector3 GetLocalScale() { return mLocalScale; }

		Vector3 Forward() { return mForward; }
		Vector3 Right() { return mRight; }
		Vector3 Up() { return mUp; }

		void SetParent(Transform* parent);
		void SetChildren(Transform* child);
		void RemoveChildren(Transform* child);
	private:
		void CalculateWorldPos();
		void CalculateLocalPos();
		void CalcluateWorldRot();
		void CalculateLocalRot();
		void CalculateWorldScale();
		void CalculateLocalScale();
	private:
		Transform* mParent;
		std::vector<Transform*> mChildren;
		Vector3 mLocalPos;
		Vector3 mWorldPos;
		Vector3 mLocalRot;
		Vector3 mWorldRot;
		Vector3 mLocalScale;
		Vector3 mWorldScale;

		Vector3 mUp;
		Vector3 mForward;
		Vector3 mRight;

		Matrix mWorld;
	};
}
