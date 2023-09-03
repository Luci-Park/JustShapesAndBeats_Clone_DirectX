#pragma once
#include "LGameObject.h"

namespace lu::graphics
{
	class Material;
}

namespace lu::JSAB
{
	class TrianglePrefab : public GameObject
	{
	public:
		TrianglePrefab(eLayerType layer);
		~TrianglePrefab();

		virtual void Initialize() override;
	private:
		std::shared_ptr<graphics::Material> CreateTriangleMat();
		std::shared_ptr<graphics::Material> CreateWhiteCircleMat();
		std::shared_ptr<graphics::Material> CreateWhiteBlueCircleMat();
	};
}

