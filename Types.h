#pragma once

#include <d3dx9.h>

using Vector3 = D3DXVECTOR3;
using Vector2 = D3DXVECTOR2;
using Matrix4 = D3DXMATRIXA16;
using Color = D3DXCOLOR;

class Rect
{
public:
	static RECT textureRectToSpriteRect(const RECT& textureRect, const Vector2& pos)
	{
		RECT rect;
		rect.left = pos.x - textureRect.right / 2;
		rect.right = pos.x + textureRect.right / 2;
		rect.top = pos.y - textureRect.bottom / 2;
		rect.bottom = pos.y + textureRect.bottom / 2;

		return rect;
	}

	static bool CollisionPos(const RECT& rect, const Vector2& pos)
	{
		if (rect.left <= pos.x && rect.right >= pos.x && rect.top <= pos.y && rect.bottom >= pos.y)
		{
			return true;
		}

		return false;
	}

	static bool CollisionRect(const RECT& rect1, const RECT& rect2)
	{
		if (rect1.left <= rect2.right && rect1.right >= rect2.left && rect1.top <= rect2.bottom && rect1.bottom >= rect2.top)
		{
			return true;
		}

		return false;
	}
};

class Math
{
public:
	static Vector2 Rotation(const Vector2& vector, const float radian)
	{
		Vector2 v;
		v.x = (vector.x * cosf(radian)) - (vector.y * sinf(radian));
		v.y = (vector.x * sinf(radian)) + (vector.y * cosf(radian));
		return v;
	}
};