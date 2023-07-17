#include "LCollider2D.h"
#include "LGameObject.h"
#include "LRenderer.h"

namespace lu
{
	UINT Collider2D::mColliderNumber = 0;
	Collider2D::Collider2D()
		:Component(eComponentType::Collider2D)
		, mTransform(nullptr)
		, mSize(Vector2::One)
		, mCenter(Vector2::Zero)
	{
		mColliderNumber++;
		mColliderID = mColliderNumber;
	}
	Collider2D::~Collider2D()
	{
	}
	void Collider2D::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
	}
	void Collider2D::Update()
	{
	}
	void Collider2D::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector3 scale = tr->GetScale();
		scale.x *= mSize.x;
		scale.y *= mSize.y;

		Vector3 pos = tr->GetPosition();
		pos.x += mCenter.x;
		pos.y += mCenter.y;

		mPosition = pos;
		mRotation = tr->GetRotation();

		graphics::DebugMesh mesh = {};
		mesh.position = pos;
		mesh.scale = scale;
		mesh.rotation = mRotation;
		mesh.type = mType;

		renderer::PushDebugMeshAttribute(mesh);
	}
	void Collider2D::Render()
	{
	}
	void Collider2D::OnCollisionEnter(Collider2D* other)
	{
		const std::vector<Script*>& scripts = GetOwner()->GetScripts();
		for (int i = 0; i < scripts.size(); i++)
			scripts[i]->OnCollisionEnter(other);
	}
	void Collider2D::OnCollisionStay(Collider2D* other)
	{
		const std::vector<Script*>& scripts = GetOwner()->GetScripts();
		for (int i = 0; i < scripts.size(); i++)
			scripts[i]->OnCollisionStay(other);
	}
	void Collider2D::OnCollisionExit(Collider2D* other)
	{
		const std::vector<Script*>& scripts = GetOwner()->GetScripts();
		for (int i = 0; i < scripts.size(); i++)
			scripts[i]->OnCollisionExit(other);
	}
}