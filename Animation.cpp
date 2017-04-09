#include "DXUT.h"
#include "Animation.h"
#include "Time.h"

Animation::Animation(Sprite* target, float rate, bool loop)
	:frameRate(rate),isLoop(loop),targetSprite(target)
{
	frames.clear();
}

void Animation::AddFrame(std::weak_ptr<Texture> frame)
{
	frames.push_back(frame);
}

void Animation::Update()
{
	if (targetSprite->__is_removed__()) { isDone = true; return; }

	if (!isDone)
	{
		frameTime += Time::deltaTime;

		if (frameTime >= frameRate)
		{
			frameTime = 0.0f;

			targetSprite->texture = frames[curAnimIndex];

			curAnimIndex++;
			if (curAnimIndex == frames.size())
			{
				curAnimIndex = 0;

				isDone = (isLoop) ? false : true;
			}
		}
	}
}
