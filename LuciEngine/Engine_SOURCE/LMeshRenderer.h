#pragma once
#include "LComponent.h"
#include "LMesh.h"
#include "LShader.h"

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

	private:
		MeshRenderer* mMesh;
		Shader* mShader;
	};
}

