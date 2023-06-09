#pragma once
#include "LGameObject.h"
#include "LRenderer.h"

namespace lu
{
	class Food : public GameObject
	{
	public:
		Food();
		virtual ~Food();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		void SetVertices();
		void LoadBuffer();
		void LoadShader();
		void SetUpState();

	private:
		std::vector<renderer::Vertex> mVertices;
		Mesh* mMesh;
		Shader* mShader;
		ConstantBuffer* mConstantBuffer;

		Vector2 mPos;
		const float mRadius = 0.05f;
	};
}

