#include "LGameObject.h"
#include "LRenderer.h"
#include "LGraphicDevice_Dx11.h"
#include "LTransform.h"

namespace lu
{
	GameObject::GameObject()
		: mState(eState::Active)
	{
		mTransform = AddComponent<Transform>();
	}

	GameObject::GameObject(Transform* parent)
	{
		mTransform->SetParent(parent);
		mTransform = AddComponent<Transform>();
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
		for (int i = 0; i < mScripts.size(); i++)
		{
			if (mScripts[i] != nullptr)
			{
				delete mScripts[i];
				mScripts[i] = nullptr;
			}
		}
	}

	void GameObject::Initialize()
	{
		for (int i = 0; i < mComponents.size(); i++)
		{
			if (mComponents[i] != nullptr)
				mComponents[i]->Initialize();
		}
		for (int i = 0; i < mScripts.size(); i++)
		{
			if (mScripts[i] != nullptr)
				mScripts[i]->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (int i = 0; i < mComponents.size(); i++)
		{
			if (mComponents[i] != nullptr)
				mComponents[i]->Update();
		}
		for (int i = 0; i < mScripts.size(); i++)
		{
			if (mScripts[i] != nullptr)
				mScripts[i]->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (int i = 0; i < mComponents.size(); i++)
		{
			if (mComponents[i] != nullptr)
				mComponents[i]->LateUpdate();
		}
		for (int i = 0; i < mScripts.size(); i++)
		{
			if (mScripts[i] != nullptr)
				mScripts[i]->LateUpdate();
		}
	}

	void GameObject::Render()
	{
		for (int i = 0; i < mComponents.size(); i++)
		{
			if (mComponents[i] != nullptr)
				mComponents[i]->Render();
		}
		for (int i = 0; i < mScripts.size(); i++)
		{
			if (mScripts[i] != nullptr)
				mScripts[i]->Render();
		}
	}

	void GameObject::SetState(eState state)
	{
		mState = state;
		const std::vector<Transform*>& children = mTransform->GetChildren();
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->GetOwner()->SetState(state);
		}
	}

}