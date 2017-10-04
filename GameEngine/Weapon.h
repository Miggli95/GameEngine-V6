#ifndef WEAPON_H
#define WEAPON_H
#include "Entity.h"
#include "NonAnimatedSprite.h"
#include "Bullet.h"
#include "NonAnimatedObjects.h"
namespace GameEngine
{
	class Weapon : NonAnimatedObjects
	{
	public:
		Weapon(Position* pos, const char* path, Entity* Owner = NULL);
		//NonAnimatedSprite* setNonAnimatedSprite(const char* texturePath, Position pos);
		void Shoot(bool color = false);
		void AimUp();
		void AimDown();
		void Flip(bool b);
		void Reload();
		void Update(SDL_Event eve, int fps, bool newInput = false);
		bool Reloaded();
		
		~Weapon();
	private:
		float angle = 0;
		bool flip = false;
		bool loaded = true;
		//NonAnimatedSprite* nonAnimatedSprite;
		Entity* Owner;
		int flipped = -1;
	};
}
#endif 


