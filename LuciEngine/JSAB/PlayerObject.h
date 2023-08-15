#pragma once
#include "..\\Engine_SOURCE\\LGameObject.h"
#include "..\\Engine_SOURCE\\LMaterial.h"
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
		void AddAnimation(GameObject* target);
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

