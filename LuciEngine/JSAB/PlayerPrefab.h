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
		PlayerPrefab(eLayerType layer);
		virtual ~PlayerPrefab();

		virtual void Initialize() override;
	private:
		std::shared_ptr<graphics::Material> CreatePlayerMat();
		std::shared_ptr<graphics::Material> CreateDashOutlineMat();
		std::shared_ptr<graphics::Material> CreateDashEffectMat();
		std::shared_ptr<graphics::Material> CreateShieldGaugeMat();
		std::shared_ptr<graphics::Material> CreateShieldMat();
	};
}

