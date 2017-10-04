#include "System.h"


namespace GameEngine
{
	System::System()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		frameBounds = { 100,100,1500,720 };
		win = SDL_CreateWindow("Game Engine", frameBounds.x, frameBounds.y,
			frameBounds.w, frameBounds.h, 0);
		ren = SDL_CreateRenderer(win, -1, 0);
	}


	System::~System()
	{
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
	}

	System sys;
}
