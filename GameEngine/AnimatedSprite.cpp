#include "AnimatedSprite.h"
#include "Position.h"
#include <iostream>
#include "GameLoop.h"

using namespace std;
namespace GameEngine
{
	int frameX = 0;
	int frameY = 0;
	int timer = 0;
	AnimatedSprite::AnimatedSprite(const char* texturePath, Position pos, int framesPerRow,int rows, bool streamable) : Sprite(texturePath,pos,streamable), framesPerRow(framesPerRow),rows(rows)
	{
		AnimatedSprite::frames = framesPerRow*rows;
		animationRate = 12;
		animationLength = AnimatedSprite::frames;
		startTime = SDL_GetTicks();

	}
	void AnimatedSprite::Update(int fps)
	{
		Animate(fps);
	}
	void AnimatedSprite::Idle()
	{
		curframe = 0;
	}

	bool AnimatedSprite::PlayedThrough()
	{
		if (curframe >= frames-1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	Position cur = Position(0, 0);


	SDL_Rect AnimatedSprite::getFrameBounds()
	{
		int frameW = getWidth() / framesPerRow;
		int frameH = getHeight() / rows;
		SDL_Rect frameBounds;
		frameBounds.x = (Sint16)(curframe % framesPerRow * frameW);
		frameBounds.y = (Sint16)(curframe / framesPerRow * frameH);
		frameBounds.w = (Sint16)(frameW);
		frameBounds.h = (Sint16)(frameH);

		return frameBounds;
	}

	void AnimatedSprite::Animate(int fps)
	{
		curframe = ((SDL_GetTicks() - startTime) * fps / 1000) % frames;
		/*timer -= fps;

		if (timer <= 0)
		{
			curframe++;
			curframe %= frames;
			timer = 10;
		}*/
	}
	
	void AnimatedSprite::Draw(Position* position)
	{
		Sprite::Draw(position);
	}

	AnimatedSprite::~AnimatedSprite()
	{
	}
}
