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
		, mRotation(Quaternion::Identity)
		, mScale(Vector3::One)
		, mLocalPosition(Vector3::Zero)
		, mLocalRotation(Quaternion::Identity)
		, mLocalScale(Vector3::One)
		, mParent(this)
	{
	}
	Transform::~Transform()
	{
	}
	void Transform::Initialize()
	{
		UpdateMatrix();
	}
	void Transform::Update()
	{
	}
	void Transform::LateUpdate()
	{
		UpdateMatrix();
	}
	void Transform::Render()
	{
	}
	void Transform::BindConstantBuffer()
	{
		renderer::TransformCB trCB = {};
		trCB.world = mTransformMatrix;
		trCB.view = Camera::GetGpuViewMatrix();
		trCB.projection = Camera::GetGpuProjectionMatrix();

		lu::graphics::ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Transform];
		cb->SetData(&trCB);
		for (int i = 0; i < (int)eShaderStage::End; i++)
			cb->Bind((eShaderStage)i);
	}
	void Transform::SetPosition(Vector3 position)
	{
		mPosition = position;
		CalculateLocalPosition();
	}
	void Transform::SetRotation(Quaternion rotation)
	{
		mRotation = rotation;
		CalculateLocalRotation();
	}
	void Transform::SetScale(Vector3 scale)
	{
		mScale = scale;
		CalculateLocalScale();
	}
	void Transform::SetPosition(float x, float y, float z)
	{
		SetPosition({ x, y, z });
	}
	void Transform::SetRotation(float x, float y, float z)
	{
		SetRotation(Quaternion::CreateFromYawPitchRoll(x, y, z));
	}
	void Transform::SetScale(float x, float y, float z)
	{
		SetScale({ x, y, z });
	}
	void Transform::SetLocalPosition(Vector3 position)
	{
		mLocalPosition = position;
		CalculateWorldPosition();
	}
	void Transform::SetLocalRotation(Quaternion rotation)
	{
		mLocalRotation = rotation;
		CalculateWorldRotation();
	}
	void Transform::SetLocalScale(Vector3 scale)
	{
		mLocalScale = scale;
		CalculateWorldScale();
	}
	void Transform::SetLocalPosition(float x, float y, float z)
	{
		SetLocalPosition({ x, y, z });
	}
	void Transform::SetLocalRotation(float x, float y, float z)
	{
		SetLocalRotation(Quaternion::CreateFromYawPitchRoll(x, y, z));
	}
	void Transform::SetLocalScale(float x, float y, float z)
	{
		SetLocalScale({ x, y, z });
	}
	void Transform::SetParent(Transform* parent)
	{
		if (mParent && mParent != this)
			mParent->RemoveChildren(this);
		mParent = parent;
		mParent->AddChildren(this);
		UpdateMatrix();
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
		if (mParent && mParent != this)
			mPosition = mParent->GetPosition() + mLocalPosition;
		else
			mPosition = mLocalPosition;
	}

	void Transform::CalculateWorldRotation()
	{
		if (mParent && mParent != this)
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
		if (mParent && mParent != this)
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
		if (mParent && mParent != this)
			mLocalPosition = mPosition - mParent->GetPosition();
		else
			mLocalPosition = mPosition;
	}

	void Transform::CalculateLocalRotation()
	{
		if (mParent && mParent != this)
		{
			Quaternion parentInverse = XMQuaternionConjugate(mParent->GetRotation());
			mLocalRotation = XMQuaternionMultiply(parentInverse, mRotation);
		}
		else
			mLocalRotation = mRotation;
	}

	void Transform::CalculateLocalScale()
	{
		if (mParent && mParent != this)
		{
			Vector3 parentScale = mParent->GetScale();
			mLocalScale.x = parentScale.y == 0 ? 0 : mScale.x / parentScale.x;
			mLocalScale.y = parentScale.y == 0 ? 0 : mScale.y / parentScale.y;
			mLocalScale.z = parentScale.z == 0 ? 0 : mScale.z / parentScale.z;
		}
		else
			mLocalScale = mScale;
	}

	void Transform::UpdateMatrix()
	{
		mTransformMatrix = Matrix::Identity;
		CalculateWorldPosition();
		CalculateWorldRotation();
		CalculateWorldScale();

		Matrix scale = Matrix::CreateScale(mScale);

		Matrix rotation = Matrix::CreateFromQuaternion(mRotation);

		Matrix position;
		position.Translation(mPosition);

		mTransformMatrix = scale * rotation * position;

		mUp = Vector3::TransformNormal(Vector3::Up, rotation);
		mForward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
	}

}