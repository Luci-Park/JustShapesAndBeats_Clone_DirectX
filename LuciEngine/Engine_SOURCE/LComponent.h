#pragma once
#include "LEntity.h"
namespace lu
{
	using namespace lu::enums;
	using namespace lu::math;
	class GameObject;
	class Component : public Entity
	{
	public:
		Component(eComponentType type);
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		GameObject* Owner() { return mOwner; }
		void SetOwner(GameObject* owner) { mOwner = owner; }
	private:
		const eComponentType mType;
		GameObject* mOwner;
	};
}

