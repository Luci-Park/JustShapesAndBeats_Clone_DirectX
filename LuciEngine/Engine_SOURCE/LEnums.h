#pragma once
namespace lu::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		MeshRenderer,
		Particle,
		Script,
		End
	};

	enum class eLayerType
	{
		Player,
		Monster,
		UI,
		End
	};
}