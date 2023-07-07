#pragma once
#include "..\\Engine_SOURCE\\LGameObject.h"

namespace lu::JSAB
{
	class PlayerObject : public GameObject
	{
	public:
		PlayerObject();
		virtual ~PlayerObject();

		virtual void Initialize() override;
	};

	class Pieces : public GameObject
	{
	public:
		Pieces(){}
		virtual ~Pieces(){}

		virtual void Initialize() override;

	private:
		GameObject* CreateLight(Vector3 pos, float rotation);
	};
}

