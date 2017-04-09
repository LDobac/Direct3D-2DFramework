#pragma once

#include <vector>
#include "Sprite.h"
#include "Texture.h"

class Animation
{
private:
	Sprite* targetSprite;

	std::vector<std::weak_ptr<Texture>> frames;

	int curAnimIndex = 0;

	float frameTime = 0.0f;
	float frameRate = 0.0f;
public:
	bool isDone = false;
	bool isLoop = false;
public:
	Animation(Sprite* target, float rate, bool loop);

	void AddFrame(std::weak_ptr<Texture> frame);

	void Update();
};