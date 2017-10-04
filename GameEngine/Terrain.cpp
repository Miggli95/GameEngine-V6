#include "Terrain.h"
#include <SDL.h>
#include "Sprite.h"
#include <SDL_image.h>
#include <iostream>
#include "System.h"
#include "NonAnimatedSprite.h"
using namespace std;
namespace GameEngine
{

	Terrain::Terrain(Position* pos, const char* path = ("Terrain.png")) : Entity(pos, setNonAnimatedSprite(path,*pos),PixelCollider::TAGTERRAIN)
	{
		//cout << path << endl;
		getPixelCollider()->setMovable(false);
		getSprite()->ExtendSurface(1000,1000);
	}

	NonAnimatedSprite* Terrain::setNonAnimatedSprite(const char* texturePath, Position pos)
	{
		nonAnimatedSprite = new NonAnimatedSprite(texturePath, pos,true);
		return nonAnimatedSprite;
	}

	void Terrain::Deform(SDL_Rect* rect, Uint8 perfection, Uint8 angle, Uint32 color)
	{
		Sprite* s = getSprite();
		Position origin = Position(s->getFrameBounds().w / 2, s->getFrameBounds().h / 2);
		SDL_Rect normalized;
		float oriX = (rect->x - (Sint16)s->getPosition().getX() + origin.getX() + s->getFrameBounds().x);
		float oriY = (rect->y - (Sint16)s->getPosition().getY() + origin.getY() + s->getFrameBounds().y);
		int r = rect->w;
		int r2 = r*r;
		int rr = r << 1;
		int area = r2 << 2;
		for (int i = 0; i < area; i++)
		{
			int tx = (i%rr) - r;
			int ty = (i / rr) - r;
			if (tx*tx + ty*ty <= r2)
			{		
				getSprite()->ChangePixel(oriX + tx, oriY + ty, color);
			}
		}
		getSprite()->Done(true);
	}

	Terrain::~Terrain()
	{
	}
}
