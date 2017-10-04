#include "NonAnimatedSprite.h"
#include <iostream>
using namespace std;
namespace GameEngine
{
	NonAnimatedSprite::NonAnimatedSprite(const char* texturePath, Position pos, bool streamable) : Sprite(texturePath, pos,streamable) {}

	SDL_Rect NonAnimatedSprite::getFrameBounds()
	{
		SDL_Rect frameBounds;
		frameBounds.x = 0;
		frameBounds.y = 0;
		frameBounds.w = (getWidth());
		frameBounds.h = (getHeight());
		return frameBounds;
	}

	NonAnimatedSprite::~NonAnimatedSprite(){}
}
