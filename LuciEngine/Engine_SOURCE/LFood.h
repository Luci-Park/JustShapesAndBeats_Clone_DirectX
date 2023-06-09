#pragma once
#include "LGameObject.h"
#include "LRenderer.h"
#include "LPlayer.h"
namespace lu
{
	extern Player* player;
	class Food : public GameObject
	{
	public:
		Food();
		virtual ~Food();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		bool DoesCollideWithPlayer();
	
	private:
		Vector2 mPos;
		const float mRadius = 0.03f;
	};
}

