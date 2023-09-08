#pragma once
#include "LComponent.h"
namespace lu
{
	class Text : public Component
	{
	public:
		Text();
		~Text();

		virtual void Render();

	public:
		std::wstring text;
		Color color;
		Vector3 offset;
		float size;

	};
}

