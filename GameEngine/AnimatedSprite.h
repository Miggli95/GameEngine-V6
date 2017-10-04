#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H
#include "Sprite.h"
#include <array>
#include <vector>
namespace GameEngine
{
	class AnimatedSprite : public Sprite
	{
	public:
	
		AnimatedSprite(const char* texturePath,Position pos,int framesPerRow = 1,int rows = 1,bool streamable = false);
		void Update(int fps);
		void Draw(Position* position);
		void Animate(int fps);
		void Idle();
		bool PlayedThrough();
		SDL_Rect getFrameBounds();
		int getCurrentFrame() { return curframe; }
		~AnimatedSprite();
		
	private:
		int startTime;
		int animationRate;
		int animationLength;
		int framesPerRow;
		int rows;
		int curframe = 0;
		int frames = 0;
	};
}
#endif

