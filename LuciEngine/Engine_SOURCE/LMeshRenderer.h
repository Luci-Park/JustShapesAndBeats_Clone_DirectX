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


	private:
	 	std::shared_ptr<Mesh> mMesh;
		std::shared_ptr<Material> mMaterial;
	};
}

