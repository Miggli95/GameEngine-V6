#include "Bullet.h"
#include <iostream>
#include <cmath>
#include "math.h"
#include "GameLoop.h"
#include "Explosion.h"
using namespace std;
namespace GameEngine
{


	Bullet::Bullet(Position* pos, float angle, const char* path, float speed, bool flipped, bool color): Entity(pos,setNonAnimatedSprite(path,*pos), PixelCollider::TAGBULLET),color(color)
	{
		if (flipped)
		{
			getSprite()->setFlipMode(SDL_FLIP_HORIZONTAL);
			getSprite()->Rotate(angle+180);
		}
		else
		{
			int temp = 180 + angle;
			angle = temp;
			getSprite()->Rotate(angle);
		}
		velocity = new Position(cos(angle*M_PI/180), sin(angle*M_PI / 180));
		*velocity *= speed;
		this->speed = speed;
	}



	NonAnimatedSprite* Bullet::setNonAnimatedSprite(const char* texturePath, Position pos)
	{
		nonAnimatedSprite = new NonAnimatedSprite(texturePath,pos);
		return nonAnimatedSprite;
	}

	void Bullet::Update(SDL_Event eve, int fps, bool newInput)
	{
		Entity::Update(eve,fps);
		getPixelCollider()->setVelocity(*velocity+&Position(0,0.4));
	}
	
	Bullet::~Bullet()
	{
		float x = getPosition()->getX();
		float y = getPosition()->getY();
		Explosion* explosion = new Explosion(new Position(x,y), "explosion.png", 4, 4);
		game.add(explosion, false);
		cout << "Bullet Destructor" << endl;
		delete velocity;
	}
}
