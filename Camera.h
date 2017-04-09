#pragma once

#include "Camera.h"
#include "Types.h"
#include "Singleton.h"

class Camera
	: public Singleton<Camera>
{
public:
	Camera() : position(0, 0) {}

	Vector2 position;
};