#pragma once
#include "LEntity.h"
#include "LComponent.h"

namespace lu
{
	class GameObject : public Entity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		eState GetState() { return mState; }

	protected:
		eState mState;
		//std::vector<Component*> mComponents;
		//int y;
		//int x;
	};
}

