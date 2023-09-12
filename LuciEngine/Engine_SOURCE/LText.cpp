#include "LText.h"
#include "LFontWrapper.h"
#include "LGameObject.h"
#include "LTransform.h"
namespace lu
{
	Text::Text()
		: Component(eComponentType::Text)
		, text()
		, color(Color::black)
		, offset(Vector3::Zero)
		, size(10)
	{
	}
	Text::~Text()
	{
	}
	void Text::Render()
	{
		Vector3 pos = Owner()->mTransform->GetPosition();
		pos += offset;
		int r = color.R() * 255;
		int g = color.G() * 255;
		int b = color.B() * 255;
		int a = color.A() * 255;
		UINT fcolor = FONT_RGBA(r, g, b, a);
		FontWrapper::DrawFont(text, pos.x, pos.y, size, fcolor);
	}
}