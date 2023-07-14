#pragma once
namespace lu::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Collider2D,
		MeshRenderer,
		Mesh,
		Particle,
		Camera,
		Script,
		End
	};

	enum class eLayerType
	{
		Player,
		Bullet,
		UI,
		Camera,
		End 
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		End
	};

	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End
	};

}