#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "Alive.h"
#include "Entity.h"
namespace GameEngine
{
	class Explosion: public Alive
	{
	public:
		Explosion(Position* pos, const char* texturePath, int frames, int rows);
		void Update(SDL_Event eve, int fps, bool newInput = false);
		~Explosion();
	};
}
#endif

