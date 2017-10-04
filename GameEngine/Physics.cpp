#include "Terrain.h"
#include "Physics.h"
#include <iostream>
#include "GameLoop.h"
#include "System.h"
#include "Explosion.h"
#include "Alive.h"
#include "Bullet.h"
#define FPS 60;
using namespace std;
namespace GameEngine
{
	const int timePerLoop = 1000 / FPS;
	typedef _List_iterator < _List_val <_List_simple_types < pair<Entity* const, PixelCollider*>>>> iter;

	void Physics::AddPixelCollider(PixelCollider* col, Entity* Owner)
	{
		colliders.insert(std::pair<Entity*, PixelCollider*>(Owner, col));
	}

	void Physics::Remove(Entity* Owner)
	{
		colliders.erase(Owner);
	}

	vector<Terrain*> getTerrain(std::unordered_map<Entity*, PixelCollider*> colliders)
	{
		vector<Terrain*> t;
		for (iter i = colliders.begin(); i != colliders.end(); i++)
		{
			if (i->second->Tag == PixelCollider::TAGTERRAIN)
				t.push_back((Terrain*)i->first);
		}
		return t;
	}

	void Deform(Terrain* terrain, Entity* col)
	{
		if (terrain != NULL)
		{
			int x = col->getPosition()->getX();
			int y = col->getPosition()->getY();
			Bullet* b = (Bullet*)col;
			Uint32 color;
			
			if (b->getColor())
			{
				Uint8 r , g , b , a;
				//cout << "color true" << endl;
				color = SDL_MapRGBA(terrain->getSprite()->format(), 100, 100, 100, 255);
				SDL_GetRGBA(color, terrain->getSprite()->format(), &r, &g, &b, &a);
				//cout << "color:" << (int)r << ":" << (int)g << ":" << (int)b << ":" << (int)a << endl;
				//cout << (int)terrain->getSprite()->format()<<endl;
			}
			else
			{
				color = terrain->getSprite()->TRANSPARENT();
			}

			terrain->Deform(new SDL_Rect{ (int)x,(int)y,40,40},NULL,360,color);
			//cout << x << endl;
			//cout << y << endl;
		}
	}
	void Gravity(PixelCollider& col)
	{
		float gravity = 100;
		float y = col.getPosition()->getY();
		gravity *= (1 / 60.0f);
		y += gravity;
		y *= 0.99;
		y *= game.getDeltaTime();
		if (col.Tag != PixelCollider::TAGBULLET)
		{
			col.setVelocity(Position(0, gravity));
		}
	}

	void Physics::Update()
	{
		SDL_Rect col;
		const int timePerLoop = 1000 / FPS;
		typedef _List_iterator < _List_val <_List_simple_types < pair<Entity* const, PixelCollider*>>>> iter;
		vector<Terrain*> terrain = getTerrain(colliders);
		for (iter i = colliders.begin(); i != colliders.end(); i++)
		{
			for (iter j = std::next(i, 1); j != colliders.end(); j++)
			{
				SDL_Rect* colPoint;
				bool collidingTerrain = (i->second->Tag == PixelCollider::TAGTERRAIN && j->second->Tag == PixelCollider::TAGTERRAIN);
				
				if (!collidingTerrain && i->second->Collision(j->second, col))
				{
					colPoint = i->second->Collision(j->second, col);
					SDL_SetRenderDrawColor(sys.getRen(), 0, 0, 255, 0);
					if (i->second->Tag == PixelCollider::TAGBULLET || j->second->Tag == PixelCollider::TAGBULLET)
					{
						if (i->second->Tag == PixelCollider::TAGBULLET)
						{
							for (Terrain* t : terrain)
							{
								Deform(t, i->first);
							}
							game.Remove(i->first);
							colliders.erase(i->first);
							return;
							//cout << "BULLETTAG" << endl;
						}

						else
						{
							for (Terrain* t : terrain)
							{
								Deform(t, j->first);
							}
							game.Remove(j->first);
							colliders.erase(j->first);
							break;
							//cout << "BULLETTAG" << endl;
						}
					}
					else
					{
						CollisionManagement(i->second, j->second, colPoint);
						CollisionManagement(j->second, i->second, colPoint);
					}

				}

				else
				{
					SDL_SetRenderDrawColor(sys.getRen(), 255, 0, 0, 255);
					setOnTerrain(terrain, j->second);
					setOnTerrain(terrain, i->second);
				}
			}
		}
	}

	void Physics::CollisionManagement(PixelCollider* colA, PixelCollider* colB, SDL_Rect* colPoint)
	{
		if (colA->Movable())
		{
			Sprite* s = colB->getSprite();
			Position origin = Position(s->getFrameBounds().w / 2, s->getFrameBounds().h / 2);
			SDL_Rect normalized;
			float x = (colPoint->x - (Sint16)s->getPosition().getX() + origin.getX() + s->getFrameBounds().x);
			float y = (colPoint->y - (Sint16)s->getPosition().getY() + origin.getY() + s->getFrameBounds().y);
			Position* vel = colB->getNormal(x, y,4); //3
			if (vel != NULL)
			{
				colA->setVelocity(*vel);
			}
		}
	}

	bool Physics::CollidingWithTerrain(/*vector<Terrain*> terrain,*/ SDL_Rect r)
	{
		bool OnGround = false;
		vector<Terrain*> terrain = getTerrain(colliders);
		for (Terrain* t : terrain)
		{
			if (t != NULL)
			{
				if (t->getPixelCollider()->CollisionWithRect(r))
				{
					//col->setGrounded(false);
					OnGround = true;
					break;
					//Gravity(*col);
				}
			}
		}

		return OnGround;
	}

	void Physics::setOnTerrain(vector<Terrain*> terrain, PixelCollider* col)
	{

		if (col->Movable() && col->Tag != PixelCollider::TAGTERRAIN)
		{
			Position origin = Position(col->getSprite()->getFrameBounds().w / 2, col->getSprite()->getFrameBounds().h / 2);
			Sprite* s = col->getSprite();
			int x = col->getPosition()->getX() - origin.getX();
			int y = col->getPosition()->getY() - origin.getY();
			int w = s->getFrameBounds().w;
			int h = s->getFrameBounds().h;
			SDL_Rect r = SDL_Rect{ x,y + h,w,5 };
			SDL_RenderFillRect(sys.getRen(), &r);

				
			if (CollidingWithTerrain(r))
			{
				col->setGrounded(true);
			}

			else
			{
				col->setGrounded(false);
				Gravity(*col);
			}
		}
	}

	Physics::~Physics()
	{
	}

	Physics physics;
}

