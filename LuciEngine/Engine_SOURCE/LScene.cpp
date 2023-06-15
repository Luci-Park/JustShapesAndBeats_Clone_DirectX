#include "LScene.h"
namespace lu
{
	Scene::Scene()
	{
	}
	Scene::~Scene()
	{

	}

	void Scene::Initialize()
	{
		for (int i = 0; i < mLayers.size(); i++)
		{
			mLayers[i]->Initialize();
		}
	}

	void Scene::Update()
	{
		for (int i = 0; i < mLayers.size(); i++)
		{
			mLayers[i]->Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (int i = 0; i < mLayers.size(); i++)
		{
			mLayers[i]->Update();
		}
	}
	void Scene::Render()
	{
		for (int i = 0; i < mLayers.size(); i++)
		{
			mLayers[i]->Render();
		}
	}
}