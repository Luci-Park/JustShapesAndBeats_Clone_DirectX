#pragma once
#include "LGameObject.h"
#include "LRenderer.h"
namespace lu
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
	private:
		void SetVertices();
		void LoadBuffer();
		void LoadShader();
		void SetUpState();

		Vector2 GetInput();

	private:
		std::vector<renderer::Vertex> mVertices;
		Mesh* mMesh;
		Shader* mShader;
		ConstantBuffer* mConstantBuffer;
		
		Vector2 mPos;
	};
}

