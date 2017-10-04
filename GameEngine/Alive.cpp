#include "Alive.h"
#include "AnimatedSprite.h"
#include <vector>
using namespace std;
namespace GameEngine
{
	Alive::Alive(Position* pos, const char* texturePath, int frames,int rows, int Tag):Entity(pos,setAnimatedSprite(texturePath,*pos,frames,rows),Tag)
	{
	}

	AnimatedSprite* Alive::setAnimatedSprite(const char* texturePath, Position pos, int frames,int rows)
	{
		animatedSprite = new AnimatedSprite(texturePath, pos, frames, rows);
		return animatedSprite;
	}
	
	void Alive::Update(SDL_Event eve, int fps, bool newInput)
	{
		Entity::Update(eve, fps);
	}

	Alive::~Alive()
	{
		//cout<<"AliveDestructor"<<endl;
	}
}
