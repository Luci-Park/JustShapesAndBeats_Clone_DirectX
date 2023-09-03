#include "guiDebugObject.h"
namespace gui
{
	DebugObject::DebugObject()
		:GameObject(lu::enums::eLayerType::End)
	{
	}
	DebugObject::~DebugObject()
	{
	}
	void DebugObject::Initialize()
	{
	}
	void DebugObject::Update()
	{
	}
	void DebugObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void DebugObject::Render()
	{
		GameObject::Render();
	}
}