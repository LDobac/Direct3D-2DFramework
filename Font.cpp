#include "DXUT.h"
#include "Font.h"

Font::Font(float fontSize, const std::wstring & fontName)
{
	D3DXCreateFont(
		DXUTGetD3D9Device(),
		fontSize, 0, 
		FW_BOLD, 
		1, 
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, 
		fontName.c_str(),
		&font);
}

Font::~Font()
{
	SAFE_RELEASE(font);
}

void Font::Draw()
{
	RECT rect;
	rect.left = position.x;
	rect.top = position.y;

	font->DrawTextW(nullptr, text.c_str(), -1, &rect, DT_NOCLIP, color);
}
