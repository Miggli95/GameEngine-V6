#include "NonAnimatedObjects.h"

namespace GameEngine
{
	NonAnimatedObjects::NonAnimatedObjects(Position* pos, const char* texturePath, int Tag) :Entity(pos, setNonAnimatedSprite(texturePath, *pos), Tag)
	{
	}

	NonAnimatedSprite* NonAnimatedObjects::setNonAnimatedSprite(const char* texturePath, Position pos)
	{
		nonAnimatedSprite = new NonAnimatedSprite(texturePath, pos);
		return nonAnimatedSprite;
	}

	void NonAnimatedObjects::Update(SDL_Event eve, int fps, bool newInput)
	{
		Entity::Update(eve, fps);
	}

	NonAnimatedObjects::~NonAnimatedObjects()
	{
	}
}
