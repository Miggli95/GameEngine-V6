#ifndef ALIVE_H
#define ALIVE_H
#include "Entity.h"
#include "Position.h"
#include "AnimatedSprite.h"
namespace GameEngine
{
	class Alive :public Entity
	{
	public:
		Alive(Position* pos, const char* texturePath, int frames, int rows, int Tag = 0);
		void Update(SDL_Event eve, int fps,bool newInput = false);
		AnimatedSprite* setAnimatedSprite(const char* texturePath, Position pos, int frames, int rows);
		~Alive();
	protected:
		Alive() {};
	private:
		int dir;
		AnimatedSprite* animatedSprite;
	};
}
#endif
