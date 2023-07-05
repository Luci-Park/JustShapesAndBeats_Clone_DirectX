#pragma once
namespace lu::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Camera,
		MeshRenderer,
		Particle,
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
}