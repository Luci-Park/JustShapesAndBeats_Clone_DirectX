#include "BackgroundObject.h"
#include "BackgroundScript.h"
#include "LMeshRenderer.h"
#include "LResources.h"

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
		mTransform->SetPosition(Vector3(0, 0, 10));
		mTransform->SetScale(Vector3(2.55, 1.9, 1));
		mBackground = AddComponent<BackgroundScript>();
		GameObject::Initialize();
		mBackground->SetBackground(BackgroundScript::Backgrounds::SKYBLUE);
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