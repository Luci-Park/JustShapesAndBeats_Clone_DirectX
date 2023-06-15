#include "LGameObject.h"
#include "LRenderer.h"
#include "LGraphicDevice_Dx11.h"

namespace lu
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Update()
	{
		// 공 움직임 구현



		// 렌더

	}

	void GameObject::LateUpdate()
	{

	}

	void GameObject::Render()
	{
	}

}