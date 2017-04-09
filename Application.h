#pragma once

#include <string>
#include "Singleton.h"
//#include "Types.h"

class Application
	: public Singleton<Application>
{
public:
	void Init(const Vector2& size)
	{
		screenSize = size;
	}

	Vector2 screenSize;
};