#include "PixelCollider.h"
#include "System.h"
#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;
namespace GameEngine
{
	PixelCollider::PixelCollider(Sprite* sprite, Position* pos, int Tag) : sprite(sprite),position(pos),Tag(Tag)
	{
		velocity = new Position(0, 0);
		//cout << Tag << endl;
		setLastPosition(position);
	}

	PixelCollider::PixelCollider() {}

	SDL_Rect PixelCollider::Intersection(const SDL_Rect& boundsA, const SDL_Rect& boundsB)
	{
		int x1 = fmax(boundsA.x, boundsB.x);
		int y1 = fmax(boundsA.y, boundsB.y);
		int x2 = fmin(boundsA.x + boundsA.w, boundsB.x + boundsB.w);
		int y2 = fmin(boundsA.y + boundsA.h, boundsB.y + boundsB.h);

		int width = x2 - x1;
		int height = y2 - y1;

		if (width > 0 && height > 0)
		{
			SDL_Rect intersect = { x1, y1, width, height };
			return intersect;
		}

		else
		{
			SDL_Rect intersect = { 0,0,0,0 };
			return intersect;
		}
	}	

	bool PixelCollider::getAlpha(int x, int y, PixelCollider * col)
	{
		Uint8 r, g, b, a;
		Sprite* s;
		if (col == NULL)
			s = this->getSprite();
		else
			s = col->getSprite();
		int alpha;
		if (s->getAlpha(x, y) == NULL)
			alpha = 0;
		else
			alpha = s->getAlpha(x, y);
		return alpha>200;
	}

	bool PixelCollider::CollisionWithRect(const SDL_Rect& rect)
	{
		
		SDL_Rect collisionRect = Intersection(rect, getSprite()->GetBounds());
		if (collisionRect.w == 0 && collisionRect.h == 0)
			return false;
		SDL_Rect normalA = NormalizeBounds(getSprite(),collisionRect);
		for (int y = 0; y <= collisionRect.h; y++)
			for (int x = 0; x <= collisionRect.w; x++)
				if (getAlpha(normalA.x + x, normalA.y+y))
					return true;
		return false;

	}
	SDL_Rect PixelCollider::NormalizeBounds(Sprite* s,const SDL_Rect & rect)
	{
		Position origin = Position(s->getFrameBounds().w / 2, s->getFrameBounds().h / 2);
		SDL_Rect normalized;
		normalized.x = rect.x - (Sint16)s->getPosition().getX() + origin.getX() + s->getFrameBounds().x;
		normalized.y = rect.y - (Sint16)s->getPosition().getY() + origin.getY() + s->getFrameBounds().y;
		normalized.w = rect.w;
		normalized.h = rect.h;
		return normalized;
	}

	SDL_Rect* PixelCollider::Collision(PixelCollider* col, SDL_Rect& collisionRect)
	{
		Sprite* other = col->getSprite();
		Sprite* sprite = getSprite();
		collisionRect = Intersection(sprite->GetBounds(),other->GetBounds());
		SDL_Rect normalA = NormalizeBounds(sprite,collisionRect);
		SDL_Rect normalB = NormalizeBounds(other,collisionRect);
		const SDL_Rect* fillRect = new SDL_Rect(collisionRect);
		if (collisionRect.w == 0 && collisionRect.h == 0)
			return NULL;

		for (int y = 0; y <= collisionRect.h; y++)
			for (int x = 0; x <= collisionRect.w; x++)
				if (getAlpha(normalA.x + x, normalA.y + y,this) && getAlpha(normalB.x + x, normalB.y + y,col))
				{
					return &collisionRect;
				}
		return NULL;
	}

	Position* PixelCollider::getNormal(int x, int y, float force)
	{
		Position position;
		float avgX = 0;
		float avgY = 0;
		for (int w = -40; w <= 40; w++)
			for (int h = -40; h <= 40; h++)
			{
				if (getAlpha( x + w, y + h))
				{
					avgX -= w;
					avgY -= h;
				}
			}
		if (!(avgX == 0 && avgY == 0))
		{
			float len = sqrt(avgX*avgX + avgY*avgY);
			position = Position(avgX / len, avgY / len);
			float angle = abs(atan(position.getX()/ position.getY())/M_PI*180);
			cout << angle << endl;

			if (angle > 47)
			{
				return new Position(position.getX()*force, 0);
			}
			else
			{
				return new Position(position.getX()*force, position.getY()*force);
			}
		}

		else
		{
			return NULL;
		}
	}

	void PixelCollider::setVelocity(Position vel, float speed)
	{
		velocity = getPosition()->setVelocity(vel, speed);
	}

	PixelCollider::~PixelCollider()
	{
		//delete position;
		//delete lastPosition;
		
		//delete velocity;
		delete collisionRect;
		//delete sprite;
	}
}
