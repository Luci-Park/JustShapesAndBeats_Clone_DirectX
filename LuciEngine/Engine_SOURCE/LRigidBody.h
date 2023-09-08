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

		void SetMass(float mass) { mMass = mass; }
		void SetVelocity(Vector3 velocity) { mVelocity = velocity; }
		void AddForce(Vector3 force);
		void UseGravity(bool use) { mbUseGravity = use; }
		Vector3 GetVelocity() { return mVelocity; }
	private:
		float mMass;
		Vector3 mForce;
		Vector3 mAccelation;
		Vector3 mVelocity;
		Vector3 mLimitVelocity;

		bool mbUseGravity;
	};
}

