#pragma once

#include <d3dx9.h>
#include <memory>
#include "Node.h"
#include "Types.h"
#include "Texture.h"

class Sprite
	: public Node,public std::enable_shared_from_this<Sprite>
{
private:
	LPD3DXSPRITE sprite;

public:
	std::weak_ptr<Texture> texture;

	Color color;
public:
	Sprite();
	Sprite(const std::string& textureName);
	virtual ~Sprite();

	virtual void Draw() override;

	RECT GetTextureRect();
	RECT GetRect();
};