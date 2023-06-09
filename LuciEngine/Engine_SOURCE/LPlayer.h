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
		void Move();
		Vector2 GetInput();

		void CheckMass();
		void UpdateConst();

	private:
		Vector2 mPos;
		float mRadius;
		int mMass;
	};
}

