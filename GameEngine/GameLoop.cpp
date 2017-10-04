#include "GameLoop.h"
#include "System.h"
#include <SDL.h>
#include "InputManager.h"
#include "Physics.h"
#include <iostream>
#include "Terrain.h"
#include "Explosion.h"
#include "TurnManager.h"
#include "Player.h"
#include <ctime>
using namespace std;

namespace GameEngine
{
	void GameLoop::add(Entity* entity, bool addCol)
	{
		entities.push_back(entity);
		if(addCol)
			physics.AddPixelCollider(entity->getPixelCollider(),entity);
	}

	void GameLoop::Remove(Entity* e)
	{
		for (int i = entities.size()-1; i >= 0; i--)
		{
			if(entities[i] == e)
			{

				delete e;
				entities.erase(entities.begin() + i);
			}
		}
	}

	void GameLoop::Left()
	{
		cout << "Left GameLoop" << endl;
	}

	void GameLoop::Right()
	{
		cout << "Right GameLoop" << endl;
	}

	int timePerLoop;
	clock_t now = clock();//SDL_GetPerformanceCounter();
	clock_t last = 0;
	bool running = true;

	void setFps(int fps)
	{
		timePerLoop = 1000 / fps;
	}

	void GameLoop::ChangeIDs()
	{
		turnM.ChangePlayerIDs();
		int numb = 0;
		for (Entity* e : entities)
		{
			if (e->getPixelCollider()->Tag == PixelCollider::TAGPLAYER)
			{
				Player* p = (Player*)e;
				turnM.addPlayer();
				numb++;
				int id = turnM.getPlayerID();
				p->ChangeID(id);
				//cout << "id" << id << endl;
				//cout << "numb" << numb << endl;
			}
		}
	}

	void GameLoop::run(int fps)
	{
		//cout << "InputManager.Update" << endl;
		while (running)
		{
			if (this->fps != fps)
			{
				this->fps = fps;
				setFps(this->fps);
			}
			//cout << (float)( now - last)/1000 << endl;
			last = now;
			now = clock();//SDL_GetPerformanceCounter();
			deltaTime = (double)((now - last))/1000;
			Uint32 nextTick = SDL_GetTicks() + timePerLoop;
			SDL_Event eve;
			while (SDL_PollEvent(&eve))
			{
				switch (eve.type)
				{
				case SDL_QUIT:
					running = false;
					break;

			/*	case SDL_KEYDOWN:
					gameEvents.push_back(eve);
					break;

				case SDL_KEYUP:
					gameEvents.push_back(eve);
					break;*/
				default :
					break;
				}
				//physics.Update();
			}
			//inputM.MouseButton();
			inputM.Update(gameEvents);
			gameEvents.clear();
			SDL_SetRenderDrawColor(sys.getRen(), 255, 255, 255, 255);
			SDL_RenderClear(sys.getRen());

			int size = entities.size();
			int id = 0;
			for (int i = size - 1; i >= 0; i--)
			{
				entities[i]->Update(eve, this->fps);
				entities[i]->Draw();
				int Tag = entities[i]->getPixelCollider()->Tag;
				if (turnM.getNumberOfPlayers() < 2)
				{
					if (Tag == PixelCollider::TAGPLAYER)
					{
						Player* p = (Player*)entities[i];
						id = p->getPlayerNumber();
					}

					//cout << "winner is player" << id << endl;
				}
				if (entities[i]->getPixelCollider()->Tag == PixelCollider::TAGBULLET || entities[i]->getPixelCollider()->Tag == PixelCollider::TAGPLAYER)
				{
					PixelCollider p = *entities[i]->getPixelCollider();
					if (!p.CollisionWithRect(sys.getFrameBounds()))
					{
						if (p.getPosition()->getX() < 0 || p.getPosition()->getX() > sys.getFrameBounds().x + sys.getFrameBounds().w
							|| p.getPosition()->getY() > sys.getFrameBounds().y + sys.getFrameBounds().h)
						{								
							physics.Remove(entities[i]);
							Remove(entities[i]);

							if (Tag == PixelCollider::TAGPLAYER)
							{
								turnM.setChangePlayer(false);
								turnM.ChangePlayerIDs();
								ChangeIDs();
								turnM.Update();
							}
							else
							{
								turnM.EndTurn();
							}
						}
					}
				}
				else
				{
					if (entities[i]->getPixelCollider()->Tag == PixelCollider::TAGEXPLOSION)
					{
						if (entities[i]->getSprite()->PlayedThrough())
						{
							Remove(entities[i]);
						}
					}
				}
			}
			physics.Update();
			SDL_RenderPresent(sys.getRen());

			int delay = nextTick - SDL_GetTicks();

			if (delay > 0)
			{
				SDL_Delay(delay);
			}
		}
	}
	GameLoop::~GameLoop()
	{
		gameEvents.clear();
		for (Entity* e : entities)
		{
			delete e;
		}
	}
	GameLoop game;
}
