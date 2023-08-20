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

		MeshRenderer* SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; return this; }
		MeshRenderer* SetMaterial(std::shared_ptr<Material> material) { mMaterial = material; return this; }
		std::shared_ptr<Mesh> GetMesh(){ return mMesh; }
		std::shared_ptr<Material> GetMaterial(){ return mMaterial; }

		MeshRenderer* SetColor(Color color) { mColor = color; return this; }
		void UseColor(bool use) { mInterpolation = use ? 1 : 0; }
		Color GetColor() { return mColor; }
		MeshRenderer* SetInterpolation(float interpolation) { mInterpolation = std::clamp(interpolation, 0.f, 1.f); return this; }

		void FlipX(bool flip) { flipX = flip; }
		void FlipY(bool flip) { flipY = flip; }

	private:
	 	std::shared_ptr<Mesh> mMesh;
		std::shared_ptr<Material> mMaterial;
		Color mColor;
		float mInterpolation;
		bool flipX;
		bool flipY;
	};
}

