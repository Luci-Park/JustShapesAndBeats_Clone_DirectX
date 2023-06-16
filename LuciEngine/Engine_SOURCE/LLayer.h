#pragma once
#include "LGameObject.h"

namespace lu
{
	class Layer
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void AddGameObject(GameObject* gameobj);

	private:
		std::vector<GameObject*> mGameObjects;
	};
}

