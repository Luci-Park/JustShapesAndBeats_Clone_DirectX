#include "LScene.h"
namespace lu
{
	Scene::Scene()
	{
		mLayers.resize((int)lu::enums::eLayerType::End);
	}
	Scene::~Scene()
	{

	}

	void Scene::Initialize()
	{
		for (int i = 0; i < mLayers.size(); i++)
		{
			mLayers[i].Initialize();
		}
	}

	void Scene::Update()
	{
		for (int i = 0; i < mLayers.size(); i++)
		{
			mLayers[i].Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (int i = 0; i < mLayers.size(); i++)
		{
			mLayers[i].LateUpdate();
		}
	}
	void Scene::Render()
	{
		for (int i = 0; i < mLayers.size(); i++)
		{
			mLayers[i].Render();
		}
	}
	void Scene::OnEnter()
	{
	}
	void Scene::OnExit()
	{
	}
	void Scene::AddGameObject(eLayerType type, GameObject* gameObj)
	{
		mLayers[(int)type].AddGameObject(gameObj);
	}
}