#ifndef GAMELOOP_H
#define GAMELOOP_H
#include "Entity.h"
#include <list>
#include <vector>
namespace GameEngine
{
	class GameLoop
	{
	public:
		void add(Entity* entity, bool addCol = true);
		void Remove(Entity * e);
		void ChangeIDs();
		void run(int fps = 60);
		int getFps() { return fps; }
		void UpdateEntities(SDL_Event eve, bool newInput = false);
		void Right();
		void Left();
		double getDeltaTime() { return deltaTime; }
		std::vector<SDL_Event> gameEvents;
		~GameLoop();
	private:
		std::vector<Entity*> entities;
		double deltaTime = 0;
		int fps = 60;
	};
	extern GameLoop game;
	
}
#endif


