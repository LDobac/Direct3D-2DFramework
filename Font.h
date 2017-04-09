#pragma once

#include <d3dx9.h>
#include "Node.h"

class Font
	: public Node
{
private:
	ID3DXFont* font;
public:
	Color color;
	std::wstring text;
public:
	Font(float fontSize, const std::wstring& fontName);
	virtual ~Font();

	virtual void Draw() override;
};