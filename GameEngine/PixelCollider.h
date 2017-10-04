#ifndef PIXELCOLLIDER_H
#define PIXELCOLLIDER_H
#include <SDL.h>
#include "Sprite.h"
#include "Position.h"
namespace GameEngine
{
	class PixelCollider
	{
	public:
		PixelCollider(Sprite* sprite, Position* pos,int Tag=1);
		PixelCollider();
		SDL_Rect Intersection(const SDL_Rect & boundsA, const SDL_Rect & boundsB);
		int Tag;
	    static const int TAGPLAYER = 1;
		static const int TAGBULLET = 2;
	    static const int TAGTERRAIN = 3;
		static const int TAGEXPLOSION = 4;
		void setMovable(bool m) { movable = m; }
		SDL_Rect* Collision(PixelCollider* col ,SDL_Rect& colRect);
		bool Movable() { return movable; }
		Position* getNormal(int x, int y, float force = 1);
		Sprite* getSprite() { return sprite; }
		void setSprite(Sprite* s) { sprite = s; }
		bool isGrounded() { return grounded; }
		void setGrounded(bool isOnGround) { grounded = isOnGround; }
		void setPosition(Position* pos) { position = pos; }
		void setLastPosition(Position* pos) { lastPosition = pos; }
		Position* getPosition() { return position; }
		Position* getLastPosition() { return lastPosition; }
		Position* getVelocity() { return velocity; }
		void setVelocity(Position vel, float speed = 1);
		bool getAlpha(int x, int y, PixelCollider* col = NULL);
		bool CollisionWithRect(const SDL_Rect & rect);
		SDL_Rect NormalizeBounds(Sprite * s, const SDL_Rect & rect);
		~PixelCollider();
	private:
		Position* position;
		Position* lastPosition;
		bool grounded;
		Position* velocity;
		SDL_Rect* collisionRect;
		bool movable = true;
		Sprite* sprite;
	};
}
#endif

