#include "BackgroundObject.h"
#include "BackgroundScript.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "LTransform.h"
namespace lu::JSAB
{
	BackgroundObject::BackgroundObject()
	{
	}
	BackgroundObject::~BackgroundObject()
	{
	}
	void BackgroundObject::Initialize()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		GetComponent<Transform>()->SetPos(Vector3(0, 0, 10));
		AddComponent<BackgroundScript>();
		GameObject::Initialize();
	}
	void BackgroundObject::Update()
	{
		GameObject::Update();
	}
	void BackgroundObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void BackgroundObject::Render()
	{
		GameObject::Render();
	}
}