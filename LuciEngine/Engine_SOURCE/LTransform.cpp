#include "LTransform.h"
#include "LRenderer.h"
#include "LConstantBuffer.h"
#include "LCamera.h"

namespace lu
{
	Transform::Transform()
		:Component(eComponentType::Transform)
		, mPosition(Vector3::Zero)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
		, mParent(nullptr)
	{
	}
	Transform::~Transform()
	{
		if (mParent != nullptr && mParent != this)
		{
			mParent->RemoveChildren(this);
		}
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

		Matrix scale = Matrix::CreateScale(mScale);

		Matrix rotation = Matrix::CreateFromQuaternion(mRotation);

		Matrix position;
		position.Translation(mPosition);

		mWorld = scale * rotation * position;

		mUp = Vector3::TransformNormal(Vector3::Up, rotation);
		mForward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);

		if (mParent && mParent != this)
		{
			mWorld *= mParent->mWorld;
		}
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
		if (mParent != nullptr && mParent != this && mParent != parent)
		{
			mParent->RemoveChildren(this);
			mParent = parent;
			parent->SetChildren(this);
		}
	}
	void Transform::SetChildren(Transform* child)
	{
		if (child != nullptr && child != this)
			mChildren.push_back(child);
	}
	void Transform::RemoveChildren(Transform* child)
	{
		auto it = std::find(mChildren.begin(), mChildren.end(), child);
		if (it != mChildren.end())
		{
			mChildren.erase(it);
		}
	}
}