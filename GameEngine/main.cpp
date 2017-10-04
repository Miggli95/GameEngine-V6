#include <iostream>
#include "InputManager.h"
#include <string>
#include <map>
#include <SDL.h>
#include "GameLoop.h"
#include "Position.h"
#include "Terrain.h"
#include "System.h"
#include "Alive.h"
#include "PLayer.h"
#include "Explosion.h"
#include "UIItem.h"
#include "Inventory.h"
using namespace std;
using namespace GameEngine;

int main(int argc, char** argv)
{
	//GitTest
	Terrain* terrain = new Terrain(&Position(0, 100), "Terrain3.png");
	Terrain* terrain2 = new Terrain(&Position(400, 100), "Terrain2.png");
	Terrain* terrain3 = new Terrain(&Position(700, 100), "Terrain.png");
	Terrain* terrain4 = new Terrain(&Position(820, 400), "Terrain3.png");
	Terrain* Trump = new Terrain(&Position(400, 200), "Trump.png");
	/*Terrain* terrain4 = new Terrain(&Position(1350, 100), "Terrain3.png");*/
	Player* player = new Player(&Position(400, 300), "walking2.png", 3, 1);
	UIItem* uiItem = new UIItem("bazooka.png", &Position(100, 200));
	UIItem* uiItem2 = new UIItem("bazooka.png", &Position(200, 400));
	Player* player2 = new Player(&Position(150, 0), "walking2.png", 3, 1);
	/*Player* player3 = new Player(&Position(200, 0), "walking2.png", 3, 1);
	Player* player4 = new Player(&Position(250, 0), "walking2.png", 3, 1);
	Player* player5 = new Player(&Position(300, 0), "walking2.png", 3, 1);
	Player* player6 = new Player(&Position(350, 0), "walking2.png", 3, 1);
	Player* player7 = new Player(&Position(400, 0), "walking2.png", 3, 1);
	Player* player8 = new Player(&Position(450, 0), "walking2.png", 3, 1);*/
	/*Player* player9 = new Player(&Position(500, 0), "walking2.png", 3, 1);
	Player* player10 = new Player(&Position(550, 0), "walking2.png", 3, 1);
	Player* player11 = new Player(&Position(600, 0), "walking2.png", 3, 1);
	Player* player12 = new Player(&Position(650, 0), "walking2.png", 3, 1);
	Player* player13 = new Player(&Position(700, 0), "walking2.png", 3, 1);
	Player* player14 = new Player(&Position(750, 0), "walking2.png", 3, 1);
	Player* player15 = new Player(&Position(800, 0), "walking2.png", 3, 1);
	Player* player16 = new Player(&Position(850, 0), "walking2.png", 3, 1);*/
	Inventory* inventory = new Inventory(&Position(0, 0));
	inventory->AddItem(uiItem);
	inventory->AddItem(uiItem2);
	//game.add(uiItem,false);
	game.add(inventory, false);
	game.add(Trump);
	game.add(terrain);
	game.add(terrain4);
	game.add(terrain2);
	game.add(terrain3);
	/*game.add(terrain4);*/
	game.add(player);
	game.add(player2);
	/*game.add(player3);
	game.add(player4);
	game.add(player5);
	game.add(player6);
	game.add(player7);
	game.add(player8);*/
	/*game.add(player9);
	game.add(player10);
	game.add(player11);
	game.add(player12);
	game.add(player13);
	game.add(player14);
	game.add(player15);
	game.add(player16);*/
	game.run(120);
	return 0;
}
