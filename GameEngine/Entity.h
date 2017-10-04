#ifndef ENTITY_H
#define ENTITY_H
#define Maximum(a,b) ((a>b) ? a:b));
#define Minimum(a,b) ((a>b) ? a:b));
#include "Position.h"
#include "Sprite.h"
#include "PixelCollider.h"

namespace GameEngine
{
	class Entity 
	{
	public:
		static Entity* getInstance(Position* pos, Sprite* sprite,int Tag = 0)
		{
			return new Entity(pos,sprite);
		}
		virtual void Update(SDL_Event eve, int fps,bool newInput = false);
		virtual void Draw();
		Sprite* getSprite() { return sprite; }
		SDL_Texture* getTexture();
		void setTexture(SDL_Texture* tex);
		Position* getPosition();
		PixelCollider* getPixelCollider() { return col; }
		void setPosition(Position* pos);
		virtual ~Entity();
	protected:
		Entity(Position* pos, Sprite* sprite, int Tag = 0);
		Entity(Position * pos, int Tag = 0);
		int getTag();
		Entity(){}
	private:
		Position* position;
		PixelCollider* col;
		Sprite* sprite;
		int Tag;
	};
}
#endif


