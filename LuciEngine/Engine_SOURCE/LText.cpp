#include "LText.h"
#include "LFontWrapper.h"
#include "LGameObject.h"
#include "LTransform.h"
#include "LApplication.h"

extern lu::Application application;

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
		pos += Vector3(application.GetWidth(), application.GetHeight(), 0) * 0.5;
		int r = color.R() * 255;
		int g = color.G() * 255;
		int b = color.B() * 255;
		int a = color.A() * 255;
		float s = size * Owner()->mTransform->GetScale().y;
		UINT fcolor = FONT_RGBA(r, g, b, a);
		FontWrapper::DrawFont(text, pos.x, pos.y, s, fcolor);
	}
}