#include "LTransform.h"
#include "LRenderer.h"
#include "LConstantBuffer.h"
#include "LCamera.h"
#include "LObject.h"

namespace lu
{
	Transform::Transform()
		:Component(eComponentType::Transform)
		, mPosition(Vector3::Zero)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
		, mLocalPosition(Vector3::Zero)
		, mLocalRotation(Vector3::Zero)
		, mLocalScale(Vector3::One)
		, mParent(this)
	{
	}
	Transform::~Transform()
	{
	}
	void Transform::Initialize()
	{
	}
	void Transform::Update()
	{
	}
	void Transform::LateUpdate()
	{
		mWorld = Matrix::Identity;

		Matrix scale = Matrix::CreateScale(mLocalScale);

		Matrix rotation = Matrix::CreateFromQuaternion(mLocalRotation);

		Matrix position;
		position.Translation(mLocalPosition);

		mWorld = scale * rotation * position;

		if (mParent && mParent != this)
		{
			mWorld *= mParent->mWorld;
		}

		mUp = Vector3::TransformNormal(Vector3::Up, rotation);
		mForward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
	}
	void Transform::Render()
	{
	}
	void Transform::BindConstantBuffer()
	{
		renderer::TransformCB trCB = {};
		trCB.mWorld = mWorld;
		trCB.mView = Camera::GetGpuViewMatrix();
		trCB.mProjection = Camera::GetGpuProjectionMatrix();

		lu::graphics::ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Transform];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::VS);
	}
	void Transform::SetParent(Transform* parent)
	{
		if (mParent != this)
			mParent->RemoveChildren(this);
		mParent = parent;
		mParent->AddChildren(this);
		CalculateWorldPosition();
		CalculateWorldRotation();
		CalculateWorldScale();
	}

	void Transform::AddChildren(Transform* child)
	{
		mChildren.push_back(child);
	}

	void Transform::RemoveChildren(Transform* child)
	{
		auto it = std::find(mChildren.begin(), mChildren.end(), child);
		if (it != mChildren.end())
			mChildren.erase(it);
	}

	void Transform::CalculateWorldPosition()
	{
		if (mParent != nullptr && mParent != this)
			mPosition = mParent->GetPosition() + mLocalPosition;
		else
			mPosition = mLocalPosition;

	}

	void Transform::CalculateWorldRotation()
	{
		if (mParent != nullptr && mParent != this)
		{
			Matrix parentRotation = Matrix::CreateFromQuaternion(mParent->GetRotation());
			Matrix localRotation = Matrix::CreateFromQuaternion(mLocalRotation);

			Matrix worldRotation = localRotation * parentRotation;
			mRotation = Quaternion::CreateFromRotationMatrix(worldRotation);
		}
		else
			mRotation = mLocalRotation;
	}

	void Transform::CalculateWorldScale()
	{
		if (mParent != this && mParent != nullptr)
		{
			Vector3 parentScale = mParent->GetScale();
			mScale.x = mLocalScale.x * parentScale.x;
			mScale.y = mLocalScale.y * parentScale.y;
		}
		else
			mScale = mLocalScale;
	}

	void Transform::CalculateLocalPosition()
	{
		if (mParent != nullptr && mParent != this)
			mLocalPosition = mParent->GetPosition() - mPosition;
		else
			mLocalPosition = mPosition;
	}

	void Transform::CalculateLocalRotation()
	{
		if (mParent != nullptr && mParent != this)
		{
			Quaternion parentInverse = XMQuaternionConjugate(mParent->GetRotation());
			mLocalRotation = XMQuaternionMultiply(parentInverse, mRotation);
		}
		else
			mLocalRotation = mRotation;
	}

	void Transform::CalculateLocalScale()
	{
		if (mParent != this && mParent != nullptr)
		{
			Vector3 parentScale = mParent->GetScale();
			mLocalScale.x = parentScale.y == 0 ? 0 : mScale.x / parentScale.x;
			mLocalScale.y = parentScale.y == 0 ? 0 : mScale.y / parentScale.y;
			mLocalScale.z = parentScale.z == 0 ? 0 : mScale.z / parentScale.z;
		}
		else
			mLocalScale = mScale;
	}

}