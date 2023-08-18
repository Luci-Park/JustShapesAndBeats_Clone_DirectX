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
		UpdateMatrix();
	}
	void Transform::Render()
	{
	}
	void Transform::BindConstantBuffer()
	{
		renderer::TransformCB trCB = {};
		trCB.world = world;
		trCB.view = Camera::GetGpuViewMatrix();
		trCB.projection = Camera::GetGpuProjectionMatrix();

		lu::graphics::ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Transform];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
	}
	void Transform::SetParent(Transform* parent)
	{
		if (mParent && mParent != this)
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

		UpdateMatrix();
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

		UpdateMatrix();
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

		UpdateMatrix();
	}

	void Transform::UpdateMatrix()
	{
		world = Matrix::Identity;
		CalculateWorldPosition();
		CalculateWorldRotation();
		CalculateWorldScale();

		Matrix scale = Matrix::CreateScale(mScale);

		Matrix rotation = Matrix::CreateFromQuaternion(mRotation);

		Matrix position;
		position.Translation(mPosition);

		world = scale * rotation * position;

		mUp = Vector3::TransformNormal(Vector3::Up, rotation);
		mForward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
	}

}