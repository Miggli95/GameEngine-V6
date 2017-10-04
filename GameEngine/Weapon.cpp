#include "Weapon.h"
#include "GameLoop.h"
#include <iostream>
using namespace std;
namespace GameEngine
{
	Weapon::Weapon(Position * pos, const char* path, Entity* Owner):NonAnimatedObjects(pos,path),Owner(Owner)
	{
		//cout << "bazooka" << endl;
		getSprite()->Rotate(90);
		game.add(this,false);

	}
	/*NonAnimatedSprite* Weapon::setNonAnimatedSprite(const char* texturePath, Position pos )
	{
		nonAnimatedSprite = new NonAnimatedSprite(texturePath, pos);
		return nonAnimatedSprite;
	}*/
	
	void Weapon::Update(SDL_Event eve, int fps, bool newInput)
	{
		Entity::Update(eve, fps, newInput);
		if (Owner == nullptr)
		{
			//cout << " Owner = NULL" << endl;
			game.Remove(this);
		}
	}

	int offset = 0;
	void Weapon::Flip(bool b)
	{
		flip = b;
		if (flip)
		{
			
			getSprite()->setFlipMode(SDL_FLIP_HORIZONTAL);
			if (offset == 0)
			{
				offset = 360;
				flipped = 1;
			}
		}

		else
		{
			
			getSprite()->setFlipMode(SDL_FLIP_NONE);
			if (offset == 360)
			{
				offset = 0;
				flipped = -1;
			}
		}
		getSprite()->Rotate((offset-angle)*flipped);

	}

	void Weapon::Reload()
	{
		loaded = true;
	}

	bool Weapon::Reloaded()
	{
		return loaded;
	}

	void Weapon::Shoot(bool color)
	{
		Position* temp = getPosition();
		if (loaded)
		{
			float h = getSprite()->getFrameBounds().h / 2;
			float x = (getSprite()->getFrameBounds().w/2)*(temp->getX()* cos((offset - angle)*flipped) - (temp->getY()) * sin((offset - angle)*flipped));
			float y = (getSprite()->getFrameBounds().w / 2)*(temp->getX()* sin((offset - angle)*flipped) + (temp->getY()) * cos((offset - angle)*flipped));
			y -= h;
			x -= h;
			game.add(Bullet::getInstance(new Position(temp->getX() + 40 * flipped, temp->getY()), (offset - angle)*flipped, "bullet.png", 50, flip,color), true);
			loaded = false;
		}
	}
	
	void Weapon::AimUp()
	{
		if (angle >= 360)
		{
			angle = 0;
		}

		angle+=2;
		getSprite()->Rotate((offset - angle)*flipped);
	}

	void Weapon::AimDown()
	{
		if (angle <= 0)
		{
			angle = 360;
		}

		angle-=2;
		getSprite()->Rotate((offset - angle)*flipped);
	}

	Weapon::~Weapon()
	{
		cout << "weaponDestructor" << endl;
	}
}
