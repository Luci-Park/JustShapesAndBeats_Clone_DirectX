#include "BackgroundObject.h"
#include "BackgroundScript.h"
#include "LMeshRenderer.h"
#include "LResources.h"
#include "LApplication.h"

extern lu::Application application;
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
		mTransform->SetPosition(Vector3(0, 0, 10));
		mTransform->SetScale(Vector3(application.GetWidth(), application.GetHeight(), 0.0f));
		mBackground = AddComponent<BackgroundScript>();
		GameObject::Initialize();
		mBackground->SetBackground(BackgroundScript::Backgrounds::PINK);
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