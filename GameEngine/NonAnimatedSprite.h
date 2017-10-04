#ifndef NONANIMATEDSPRITE_H
#define NONANIMATEDSPRITE_H
#include "Sprite.h"

namespace GameEngine
{
	class NonAnimatedSprite : public Sprite
	{
	public:
		NonAnimatedSprite(const char* texturePath,Position pos, bool streamable = false);
		~NonAnimatedSprite();
		SDL_Rect getFrameBounds();
	};
}
#endif


