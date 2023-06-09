#pragma once
#include "LEntity.h"
#include "LGameObject.h"
#include "LPlayer.h"
namespace lu
{
	Player* player;
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		std::vector<GameObject*> mGameObjects;
		float mTimer;
		float mSpawnTime;
	};
}

