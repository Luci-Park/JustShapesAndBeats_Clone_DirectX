#include "LTransform.h"
#include "LRenderer.h"
#include "LConstantBuffer.h"

namespace lu
{
	Transform::Transform()
		:Component(eComponentType::Transform)
		, mLocalPos(Vector3::Zero)
		, mWorldPos(Vector3::Zero)
		, mLocalRot(Vector3::Zero)
		, mWorldRot(Vector3::Zero)
		, mLocalScale(Vector3::One)
		, mWorldScale(Vector3::One)
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
		CalculateWorldPos();
		CalculateWorldScale();
	}
	void Transform::LateUpdate()
	{
		mWorld = Matrix::Identity;
		Matrix scale = Matrix::CreateScale(mWorldScale);

		Matrix rotation = Matrix::CreateRotationX(mWorldRot.x);
		rotation *= Matrix::CreateRotationY(mWorldRot.y);
		rotation *= Matrix::CreateRotationZ(mWorldRot.z);

		Matrix position;
		position.Translation(mWorldPos);

		mWorld = scale * rotation * position;

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
		lu::graphics::ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Transform];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::VS);
	}
	void Transform::SetParent(Transform* parent)
	{
		if (mParent != nullptr && mParent != this && mParent != parent)
		{
			mParent->RemoveChildren(this);
		}
		mParent = parent;
		parent->SetChildren(this);
		CalculateWorldPos();
		CalculateWorldScale();
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
	void Transform::CalculateWorldPos()
	{
		if (mParent != nullptr && mParent != this)
			mWorldPos = mLocalPos + mParent->GetPos();
		else
			mWorldPos = mLocalPos;
	}
	void Transform::CalculateLocalPos()
	{
		if (mParent != nullptr && mParent != this)
			mLocalPos = mWorldPos - mParent->GetPos();
		else
			mLocalPos = mWorldPos;
	}
	void Transform::CalcluateWorldRot()
	{
	}
	void Transform::CalculateLocalRot()
	{
	}
	void Transform::CalculateWorldScale()
	{
		if (mParent != nullptr && mParent != this)
		{
			Vector3 parentScale = mParent->GetScale();
			mWorldScale.x = mLocalScale.x * parentScale.x;
			mWorldScale.y = mLocalScale.y * parentScale.y;
			mWorldScale.z = mLocalScale.y * parentScale.y;
		}
		else
			mWorldScale = mLocalScale;
	}
	void Transform::CalculateLocalScale()
	{
		if (mParent != nullptr && mParent != this)
		{
			Vector3 parentScale = mParent->GetScale();
			mLocalScale.x = parentScale.y == 0 ? 0 : mWorldScale.x / parentScale.x;
			mLocalScale.y = parentScale.y == 0 ? 0 : mWorldScale.y / parentScale.y;
			mLocalScale.z = parentScale.z == 0 ? 0 : mWorldScale.z / parentScale.z;
		}
		else
			mLocalScale = mWorldScale;
	}
}