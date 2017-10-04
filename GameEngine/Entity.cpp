#include "Entity.h"
#include <iostream>
#include <SDL.h>
using namespace std;
namespace GameEngine
{
	Entity::Entity(Position* pos,Sprite* sprite, int Tag) : position(pos),sprite(sprite), Tag(Tag)
	{
		position->setVelocity(Position(0, 0));
		if(sprite!=NULL)
			col = new PixelCollider(this->sprite, position, Tag);
		//cout << Tag << endl;
	}

	Entity::Entity(Position* pos, int Tag) : position(pos), Tag(Tag) { col = new  PixelCollider(); }

	int Entity::getTag()
	{
		return Tag;
	}

	Position* Entity::getPosition() { return Entity::position; }
	void Entity::setPosition(Position* pos) { Entity::position = pos; }
	SDL_Texture* Entity::getTexture()
	{
		return sprite->getTexture();
	}

	void Entity::Update(SDL_Event eve, int fps,bool newInput)
	{
		//setPosition(col->getPosition());
		if(sprite!=NULL)
			sprite->setPosition(*getPosition());
	}

	void Entity::setTexture(SDL_Texture* tex)
	{
		sprite->setTexture(tex);
	}

	void Entity::Draw()
	{
		sprite->Draw(position);
	}

	Entity::~Entity()
	{
		//cout << "EntityDestructor" << endl;
		delete col;
		delete sprite;
	}
}
