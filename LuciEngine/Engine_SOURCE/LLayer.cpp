#include "LLayer.h"
namespace lu
{
	Layer::Layer()
	{
	}
	Layer::~Layer()
	{
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			if (mGameObjects[i] != nullptr)
			{
				delete mGameObjects[i];
				mGameObjects[i] = nullptr;
			}
		}
	}
	void Layer::Initialize()
	{
	}
	void Layer::Update()
	{
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			if(mGameObjects[i] && mGameObjects[i]->GetState() == GameObject::eState::Active)
				mGameObjects[i]->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			if (mGameObjects[i] && mGameObjects[i]->GetState() == GameObject::eState::Active)
				mGameObjects[i]->LateUpdate();
		}
	}
	void Layer::Render()
	{
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			if (mGameObjects[i] && mGameObjects[i]->GetState() == GameObject::eState::Active)
				mGameObjects[i]->Render();
		}
	}
	void Layer::Destroy()
	{
		for (auto it = mGameObjects.begin(); it != mGameObjects.end(); )
		{
			if ((*it)->GetState() == GameObject::eState::Destory)
			{
				auto iter = mGameObjects.erase(it);
				delete *iter;
			}
			else
			{
				it++;
			}
		}
	}
	void Layer::AddGameObject(GameObject* gameobj)
	{
		mGameObjects.push_back(gameobj);
	}
}