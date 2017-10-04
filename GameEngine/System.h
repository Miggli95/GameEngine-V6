#ifndef SYSTEM_H
#define SYSTEM_H
#include <SDL.h>
namespace GameEngine
{
	class System
	{
	public:
		System();
		SDL_Renderer* getRen() { return ren; }
		SDL_Window* getWin() { return win; }
		SDL_Rect getFrameBounds() { return frameBounds; }
		Uint32 format() { return SDL_GetWindowPixelFormat(win); }
		SDL_PixelFormat* surfaceFormat() { return SDL_GetWindowSurface(win)->format; }
		~System();

	private:
		SDL_Window* win;
		SDL_Renderer* ren;
		SDL_Rect frameBounds;
	};
	extern System sys;
}
#endif;

