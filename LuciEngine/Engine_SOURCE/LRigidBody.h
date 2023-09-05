#pragma once
#include "LComponent.h"
namespace lu
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void AddForce(Vector3 force) { mForce += force; }
		void SetMass(float mass) { mMass = mass; }
		void SetGround(bool ground) { mbGround = ground; }
		void SetFloat(bool b) { mbFloat = b; }
		void SetVelocity(Vector3 velocity) { mVelocity = velocity; }

		Vector3 GetVelocity() { return mVelocity; }
		bool GetGround() { return mbGround; }
		bool GetFloat() { return mbFloat; }
	private:
		float mMass;
		Vector3 mForce;
		Vector3 mAccelation;
		Vector3 mVelocity;
		Vector3 mLimitVelocity;

		Vector3 mGravity;

		bool mbGround;
		bool mbFloat;
	};
}

