#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"
#include "NonAnimatedSprite.h"
#include "Explosion.h"
namespace GameEngine
{
	class Bullet :public Entity
	{
	public:
		static Bullet* getInstance(Position* pos, float angle, const char* path, float speed = 1, bool flipped = false, bool  color = false)
		{
			return new Bullet(pos,angle,path, speed, flipped, color);
		}
		bool getColor() { return color; }
		void Update(SDL_Event eve, int fps, bool newInput = false);
	protected:
		Bullet(Position* pos, float angle, const char* path, float speed, bool flipped, bool color);
		NonAnimatedSprite* setNonAnimatedSprite(const char* texturePath, Position pos);

		~Bullet();

	private:
		Position* velocity;
		NonAnimatedSprite* nonAnimatedSprite;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		bool color;
		float speed;
	};
}
#endif

