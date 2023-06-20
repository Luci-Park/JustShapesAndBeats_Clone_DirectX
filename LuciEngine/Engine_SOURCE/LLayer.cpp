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
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Initialize();
		}
	}
	void Layer::Update()
	{
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Update();
		}
	}
	void Layer::LateUpdate()
	{
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->LateUpdate();
		}
	}
	void Layer::Render()
	{
		for (int i = 0; i < mGameObjects.size(); i++)
		{
			mGameObjects[i]->Render();
		}
	}
	void Layer::AddGameObject(GameObject* gameobj)
	{
		mGameObjects.push_back(gameobj);
	}
}