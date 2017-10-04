#ifndef PLAYER_H
#define PLAYER_H
#include "InputManager.h"
#include <string>
#include "Alive.h"
#include "Position.h"
#include "Weapon.h"
namespace GameEngine
{
	class Player : public Alive
	{
	public:
		Player(Position* position, const char* texturePath, int frames = 1, int rows = 1, 
			std::string up = "W", std::string down = "S", std::string left = "A",
			std::string right = "D");
		int getPlayerHealth();
		void ChangeID(int ID);
		Player() {}
		void Update(SDL_Event eve, int fps, bool newInput = false);
		void Damage(float damage);
		void Teraform();
		void Reload();
		void Jump();
		bool myTurn();
		void Up();
		void Shoot();
		void Down();
		void Left();
		void Right();
		int getID();
		int getPlayerNumber();
		~Player();
	private:
		Weapon* weapon;
		int fps = 60;
		bool shoot = false;
		int playerId;
		int playerNumber;
		SDL_Rect topCollider;
		bool jump = false;
		int playerHealth = 100;
	};
}
#endif

