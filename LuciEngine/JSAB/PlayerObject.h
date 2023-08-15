#pragma once
#include "..\\Engine_SOURCE\\LGameObject.h"

class lu::graphics::Material;
namespace lu::JSAB
{
	class PlayerObject : public GameObject
	{
	public:
		PlayerObject();
		virtual ~PlayerObject();

		virtual void Initialize() override;
	private:
		std::shared_ptr<lu::graphics::Material> CreatePlayerMat();
		std::shared_ptr<lu::graphics::Material> CreateDashOutlineMat();
		std::shared_ptr<lu::graphics::Material> CreateDashEffectMat();
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

