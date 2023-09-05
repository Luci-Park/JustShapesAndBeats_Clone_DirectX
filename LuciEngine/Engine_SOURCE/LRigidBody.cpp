#include "LRigidBody.h"
#include "LTime.h"
#include "LTransform.h"
#include "LGameObject.h"

namespace lu
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		, mForce(Vector3::Zero)
		, mAccelation(Vector3::Zero)
		, mVelocity(Vector3::Zero)
		, mLimitVelocity(Vector3::Zero)
		, mbFloat(false)
	{
		mbGround = false;
		mGravity = Vector3(0.0f, -980.f, 0.0f);
		mLimitVelocity.y = 2000.0f;
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::Initialize()
	{
	}

	void Rigidbody::Update()
	{
		mAccelation = mForce / mMass;
		mVelocity += mAccelation * Time::DeltaTime();

		if (mbFloat == false)
		{
			if (mbGround)
			{
				// 땅 위에 있을 때
				Vector3 gravity = mGravity;
				gravity.Normalize();

				float dot = mVelocity.Dot(gravity);
				mVelocity -= gravity * dot;
			}
			else
			{
				mVelocity += mGravity * Time::DeltaTime();
			}
		}

		// limit gravity accelation
		Vector3 gravity = mGravity;
		gravity.Normalize();

		float dot = mVelocity.Dot(gravity);
		gravity = gravity * dot;

		//Vector3 sideVelocity = mVelocity - gravity;

		if (mLimitVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitVelocity.y;
		}

		Transform* tr = Owner()->mTransform;
		Vector3 pos = tr->GetPosition();
		pos = pos + mVelocity * Time::DeltaTime();
		tr->SetPosition(pos);
		mForce = Vector3::Zero;
	}

	void Rigidbody::LateUpdate()
	{
	}

	void Rigidbody::Render()
	{
	}
}