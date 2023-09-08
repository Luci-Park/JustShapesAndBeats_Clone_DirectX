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