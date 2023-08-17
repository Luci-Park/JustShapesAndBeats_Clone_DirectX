#include "LEntity.h"


namespace lu
{
	Entity::Entity()
		: mName(L"")
		, mColliderID((UINT64)this)
		, mState(eState::Active)
	{

	}

	Entity::~Entity()
	{
	}

	void Entity::SetActive(bool active)
	{
		SetState(active ? eState::Active : eState::InActive);
	}

}
