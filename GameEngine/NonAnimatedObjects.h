#ifndef NONANIMATEDOBJECTS_H
#define NONANIMATEDOBJECTS_H
#include "Entity.h"
#include "NonAnimatedSprite.h"

namespace GameEngine
{
	class NonAnimatedObjects : public Entity
	{
		public:
			NonAnimatedObjects(Position* pos, const char* texturePath, int Tag = 0);
			void Update(SDL_Event eve, int fps, bool newInput = false);
			NonAnimatedSprite* setNonAnimatedSprite(const char* texturePath, Position pos);
			~NonAnimatedObjects();
		protected:
			NonAnimatedObjects() {};
		private:
			int dir;
			NonAnimatedSprite* nonAnimatedSprite;
	};
	
}
#endif

