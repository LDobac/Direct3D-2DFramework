#pragma once

#include <d3dx9.h>
#include <list>
#include <memory>
#include "Singleton.h"

struct Texture
{
	std::string name;
	RECT textureRect;
	LPDIRECT3DTEXTURE9 texture;
};

class TexturePool
	: public Singleton<TexturePool>
{
private:
	std::list<std::shared_ptr<Texture>> textureCache;
public:
	TexturePool() {}
	virtual ~TexturePool();

	std::weak_ptr<Texture> LoadTexture(const std::string& textureName);
};