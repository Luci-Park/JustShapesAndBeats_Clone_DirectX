#pragma once
#include "LuciEngine.h"

namespace lu
{
	class Entity
	{
	public:
		enum eState
		{
			Active,
			InActive,
			Destory,
		};
		Entity();
		virtual ~Entity();
		void SetID(UINT64 id) { mColliderID = id; }
		UINT64 GetID() { return mColliderID; }

		virtual eState GetState() { return mState; }
		virtual void SetState(eState state) { 
			mState = state; }
		bool IsActive() { return mState == Entity::eState::Active; }
		void SetActive(bool active);
	protected:
		eState mState;
		UINT64 mColliderID;
	};
}
