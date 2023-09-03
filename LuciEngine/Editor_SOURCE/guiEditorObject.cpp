#include "guiEditorObject.h"
namespace gui
{
	EditorObject::EditorObject()
		:GameObject(lu::enums::eLayerType::End)
	{
	}
	EditorObject::~EditorObject()
	{
	}
	void EditorObject::Initialize()
	{
		GameObject::Initialize();
	}
	void EditorObject::Update()
	{
		GameObject::Update();
	}
	void EditorObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void EditorObject::Render()
	{
		GameObject::Render();
	}
}