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
		, mbUseGravity(false)
		, mDrag(0)
	{
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
		if (abs(mDrag) > 0)
		{
			Vector3 dir;
			mVelocity.Normalize(dir);
			Vector3 resultVel = mVelocity + dir * mDrag * -1 * Time::DeltaTime();
			if (mVelocity.Dot(resultVel) < 0)
				mVelocity = Vector3::Zero;
			else
				mVelocity = resultVel;
		}
		if (mbUseGravity)
			AddForce(Vector3::Up * -9.8);

		Vector3 pos = Owner()->mTransform->GetPosition();
		pos += mVelocity * Time::DeltaTime();
		Owner()->mTransform->SetPosition(pos);
	}

	void Rigidbody::LateUpdate()
	{
		
	}

	void Rigidbody::Render()
	{
	}
	void Rigidbody::AddForce(Vector3 force)
	{
		mVelocity += force * Time::DeltaTime();
	}
}