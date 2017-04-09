#include "DXUT.h"
#include "Sprite.h"

Sprite::Sprite()
	:color(1.0f, 1.0f, 1.0f, 1.0f)
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);
}

Sprite::Sprite(const std::string & textureName)
	:color(1.0f,1.0f,1.0f,1.0f)
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);

	texture = TexturePool::GetInstance()->LoadTexture(textureName);
}

Sprite::~Sprite()
{
	SAFE_RELEASE(sprite);
}

void Sprite::Draw()
{
	std::shared_ptr<Texture> sTexture = texture.lock();
	if (sTexture == nullptr) { return; }

	Vector3 center(sTexture->textureRect.right, sTexture->textureRect.bottom, 0);
	center *= 0.5f;
	sprite->SetTransform(&GetTransform());

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(sTexture->texture, nullptr, &center, nullptr, color);
	sprite->End();
}

RECT Sprite::GetTextureRect()
{
	return texture.lock()->textureRect;
}

RECT Sprite::GetRect()
{
	auto tex = texture.lock();

	return Rect::textureRectToSpriteRect(tex->textureRect, position);
}
