#include "LGameObject.h"
#include "LRenderer.h"
#include "LGraphicDevice_Dx11.h"
#include "LTransform.h"

namespace lu
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		for (int i = 0; i < mComponents.size(); i++)
		{
			if (mComponents[i] != nullptr)
			{
				delete mComponents[i];
				mComponents[i] = nullptr;
			}
		}
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Update()
	{
		for (int i = 0; i < mComponents.size(); i++)
		{
			if (mComponents[i] != nullptr)
				mComponents[i]->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (int i = 0; i < mComponents.size(); i++)
		{
			if (mComponents[i] != nullptr)
				mComponents[i]->LateUpdate();
		}
	}

	void GameObject::Render()
	{
		for (int i = 0; i < mComponents.size(); i++)
		{
			if (mComponents[i] != nullptr)
				mComponents[i]->Render();
		}
	}

}