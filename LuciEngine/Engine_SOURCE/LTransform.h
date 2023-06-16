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
		virtual void Render() override;

		void BindConstantBuffer();

		void SetPos(Vector3 pos) { mWorldPos = pos; CalculateLocalPos(); }
		void SetLocalPos(Vector3 pos) { mLocalPos = pos; CalculateWorldPos(); }
		void SetScale(Vector3 scale) { mWorldScale = scale; CalculateLocalScale(); }
		void SetLocalScale(Vector3 scale) { mLocalScale = scale; CalculateWorldScale(); }
		Vector3 GetPos() { return mWorldPos; }
		Vector3 GetScale() { return mWorldScale; }
		Vector3 GetLocalPos() { return mLocalPos; }
		Vector3 GetLocalScale() { return mLocalScale; }

		void SetParent(Transform* parent);
		void SetChildren(Transform* child);
		void RemoveChildren(Transform* child);
	private:
		void CalculateWorldPos();
		void CalculateLocalPos();
		void CalculateWorldScale();
		void CalculateLocalScale();
	private:
		Transform* mParent;
		std::vector<Transform*> mChildren;
		Vector3 mLocalPos;
		Vector3 mLocalScale;
		Vector3 mWorldPos;
		Vector3 mWorldScale;
	};
}
