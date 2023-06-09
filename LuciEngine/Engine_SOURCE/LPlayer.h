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

		float GetRadius() { return mRadius; }
		Vector2 GetPos() { return mPos; }
		void AddMass() { mMass++; }
	private:
		void SetVertices();
		void LoadBuffer();
		void LoadShader();
		void SetUpState();

		void Move();
		Vector2 GetInput();

		void CheckMass();
		void UpdateConst();

	private:
		std::vector<renderer::Vertex> mVertices;
		Mesh* mMesh;
		Shader* mShader;
		ConstantBuffer* mConstantBuffer;
		
		Vector2 mPos;
		float mRadius;
		int mMass;
	};
}

