#include "Explosion.h"
#include "GameLoop.h"
#include <vector>
#include <iostream>
#include "TurnManager.h"
using namespace std;
namespace GameEngine
{

	Explosion::Explosion(Position* pos, const char* texturePath, int frames, int rows):Alive(pos,texturePath,frames,rows,PixelCollider::TAGEXPLOSION)
	{
		turnM.setChangeTimer(0);
		turnM.EndTurn();
	}

	void Explosion::Update(SDL_Event eve, int fps,bool newInput)
	{
		Alive::Update(eve, 1/game.getDeltaTime());
		getSprite()->Update(30);
	}
	Explosion::~Explosion()
	{
		//cout << "ExplosionDestructor" << endl;
	}
}
