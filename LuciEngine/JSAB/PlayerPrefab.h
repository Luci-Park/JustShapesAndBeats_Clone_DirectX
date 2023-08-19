#pragma once
#include "..\\Engine_SOURCE\\LGameObject.h"

namespace lu::graphics
{
	class Material;
}
namespace lu::JSAB
{
	class PlayerPrefab : public GameObject
	{
	public:
		PlayerPrefab();
		virtual ~PlayerPrefab();

		virtual void Initialize() override;
	private:
		std::shared_ptr<graphics::Material> CreatePlayerMat();
		std::shared_ptr<graphics::Material> CreateDashOutlineMat();
		std::shared_ptr<graphics::Material> CreateDashEffectMat();
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

