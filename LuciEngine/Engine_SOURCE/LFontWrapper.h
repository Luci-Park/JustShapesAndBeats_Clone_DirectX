#pragma once
#include "LuciEngine.h"
#include "..\\Extern\\FW1FontWrapper\\Include\\FW1FontWrapper.h"
#include "..\\Extern\\FW1FontWrapper\\Include\\FW1CompileSettings.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Extern\\FW1FontWrapper\\Library\\Debug\\FW1FontWrapperL.lib")
#else
#pragma comment(lib, "..\\Extern\\FW1FontWrapper\\Library\\Debug\\FW1FontWrapper.lib")
#endif

namespace lu
{
#define FONT_RGBA(r, g, b, a) (((((BYTE)a << 24 ) | (BYTE)b << 16) | (BYTE)g << 8) | (BYTE)r)

	class FontWrapper
	{
	public:
		static bool Initialize();
		static void DrawFont(const std::wstring text, float x, float y, float size, UINT rgb);
		static void Release();


	private:
		static IFW1Factory* mFW1Factory;
		static IFW1FontWrapper* mFontWrapper;
	};
}

