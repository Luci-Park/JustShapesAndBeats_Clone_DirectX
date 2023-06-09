#include "LScene.h"
#include "LPlayer.h"
#include "LFood.h"
#include "LTime.h"
namespace lu
{
	Scene::Scene()
		: mTimer(0)
		, mSpawnTime(15.0f)
	{
	}
	Scene::~Scene()
	{

	}

	void Scene::Initialize()
	{
		// 여기서 초기 게임 맵데이터를 세팅해줘야 한다.
		player = new Player();
		mGameObjects.push_back(player);
		for (int i = 0; i < 10; i++)
			mGameObjects.push_back(new Food());
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Initialize();
		}	
	}

	void Scene::Update()
	{
		for (auto it = mGameObjects.begin(); it != mGameObjects.end();)
		{
			GameObject* gameObj = *it;
			if (gameObj->GetState() == GameObject::eState::Dead)
			{
				delete gameObj;
				it = mGameObjects.erase(it);
			}
			else
			{
				gameObj->Update();
				++it;
			}
		}
		
		mTimer += Time::DeltaTime();
		if (mTimer >= mSpawnTime)
		{
			mTimer -= mSpawnTime;
			mGameObjects.push_back(new Food());
		}
	}

	void Scene::LateUpdate()
	{
	}
	void Scene::Render()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Render();
		}
	}
}