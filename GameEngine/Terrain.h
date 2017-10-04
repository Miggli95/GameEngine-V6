#ifndef TERRAIN_H
#define TERRAIN_H
#include "Entity.h"
#include <SDL.h>
#include "NonAnimatedSprite.h"

namespace GameEngine
{
	class Terrain :
		public Entity
	{
	public:
		Terrain(Position* pos,const char* path);
		NonAnimatedSprite* setNonAnimatedSprite(const char* texturePath, Position pos);
		void Deform(SDL_Rect* rect, Uint8 perfection = 1, Uint8 angle = 360, Uint32 color = NULL);
		void MergeTerrain(); //implement
		~Terrain();
	private:
		NonAnimatedSprite* nonAnimatedSprite;
	};
}
#endif

