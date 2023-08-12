#pragma once
#include "LComponent.h"
#include "LMesh.h"
#include "LMaterial.h"

namespace lu
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; }
		void SetMaterial(std::shared_ptr<Material> material){ mMaterial = material; }
		std::shared_ptr<Mesh> GetMesh(){ return mMesh; }
		std::shared_ptr<Material> GetMaterial(){ return mMaterial; }

		void SetColor(Color color) { mColor = color; }
		void UseColor(bool use) { mInterpolation = use ? 1 : 0; }
		Color GetColor() { return mColor; }
		void SetInterpolation(float interpolation) { mInterpolation = std::clamp(interpolation, 0.f, 1.f); }

	private:
	 	std::shared_ptr<Mesh> mMesh;
		std::shared_ptr<Material> mMaterial;
		Color mColor;
		float mInterpolation;
	};
}

