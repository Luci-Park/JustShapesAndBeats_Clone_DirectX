#include "LScene.h"
#include "LRenderer.h"
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
		for (int i = 0; i < cameras.size(); i++)
		{
			if (cameras[i] == nullptr)
				continue;

			cameras[i]->Render();
		}
		mainCamera = cameras.size() > 0 ? cameras[0] : nullptr;

		for (int i = 0; i < mLayers.size(); i++)
		{
			mLayers[i].Render();
		}
	}
	void Scene::Destroy()
	{
		for (int i = 0; i < mLayers.size(); i++)
		{
			mLayers[i].Destroy();
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
	void Scene::AddCamera(Camera* camera)
	{
		cameras.push_back(camera);
		mainCamera = cameras.size() > 0 ? cameras[0] : nullptr;
	}
}