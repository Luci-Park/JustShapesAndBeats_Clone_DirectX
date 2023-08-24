#include "LScript.h"
namespace lu
{
	Script::Script()
		:Component(enums::eComponentType::Script)
	{
	}
	Script::~Script()
	{
	}
	void Script::Initialize()
	{
	}
	void Script::Update()
	{
	}
	void Script::LateUpdate()
	{
	}
	void Script::Render()
	{
	}
	void Script::SetState(eState state)
	{
		Entity::mState = state;
		if (Entity::Active == state)
			OnEnable();
		else if (Entity::InActive == state)
			OnDisable();
	}
}