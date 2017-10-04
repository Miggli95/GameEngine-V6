#ifndef PHYSICS_H
#define PHYSICS_H
#include "PixelCollider.h"
#include <vector>
#include <unordered_map>
#include "Terrain.h"
namespace GameEngine
{
	class Physics
	{
	public:
		void Init();
		void AddPixelCollider(PixelCollider* col, Entity* Owner);
		void Update();
		void CollisionManagement(PixelCollider * colA, PixelCollider * colB, SDL_Rect * colPoint);
		bool CollidingWithTerrain(/*vector<Terrain*> terrain,*/ SDL_Rect r);
		void setOnTerrain(std::vector<Terrain*> terrain, PixelCollider * col);
		void Remove(Entity* Owner);
		~Physics();
	private:
		std::unordered_map<Entity*,PixelCollider*> colliders;
		int startTime;
		int rate;
	};

	extern Physics physics;
}
#endif


