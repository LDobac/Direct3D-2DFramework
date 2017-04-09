#include "DXUT.h"
#include "Texture.h"
#include <memory>
#include "Types.h"

TexturePool::~TexturePool()
{
	for (auto it = textureCache.begin(); it != textureCache.end(); it++)
	{
		SAFE_RELEASE((*it)->texture);
	}
	textureCache.clear();
}

std::weak_ptr<Texture> TexturePool::LoadTexture(const std::string & textureName)
{
	for (auto it = textureCache.begin(); it != textureCache.end(); it++)
	{
		if ((*it)->name == textureName)
		{
			return std::weak_ptr<Texture>((*it));
		}
	}

	Texture* newTexture = new Texture();

	D3DXIMAGE_INFO imageInfo;
	if (FAILED(D3DXCreateTextureFromFileExA(
		DXUTGetD3D9Device()
		, textureName.c_str(),
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		1, 0,
		D3DFMT_A8B8G8R8, D3DPOOL_MANAGED,
		D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &imageInfo, nullptr, &newTexture->texture)))
	{
		DXUTOutputDebugString(L"텍스쳐가 존재 하지 않음!  \n");

		
		return std::weak_ptr<Texture>();
	}
	newTexture->name = textureName;
	newTexture->textureRect = RECT{ 0,0,(LONG)imageInfo.Width ,(LONG)imageInfo.Height };

	auto sPtr = std::shared_ptr<Texture>(newTexture);
	textureCache.push_back(sPtr);

	return std::weak_ptr<Texture>(sPtr);
}
