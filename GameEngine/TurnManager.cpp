#include "TurnManager.h"
#include <iostream>
using namespace std;
namespace GameEngine
{
	TurnManager::TurnManager() {}
	void TurnManager::addPlayer()
	{
		numberOfPlayers++;
	}

	void TurnManager::removePlayer()
	{
		numberOfPlayers--;
	}

	int TurnManager::getCurrentPlayer()
	{
		return currentPlayer;
	}

	int TurnManager::getNumberOfPlayers()
	{
		return numberOfPlayers;
	}

	void TurnManager::Update()
	{
		if (currentPlayer>1 && changePlayer == false)
		{
			currentPlayer--;
		}
	}

	bool TurnManager::getChangePlayer()
	{
		return changePlayer;
	}

	void TurnManager::setChangePlayer(bool change)
	{
		changePlayer = change;
	}

	void TurnManager::EndTurn()
	{
		if (changePlayer)
		{
			//cout << "Endturn" << endl;
			currentPlayer++;
			if (currentPlayer > numberOfPlayers)
			{
				currentPlayer = 1;
			}
			changePlayer = false;
		}
	}

	void TurnManager::ChangePlayerIDs()
	{
		numberOfPlayers = 0;
	}

	int TurnManager::getPlayerID()
	{
		return numberOfPlayers;
	}

	void TurnManager::IncreaseChangeTimer(int to)
	{
		if (changeTimer <= to)
		{
			changeTimer++;
		}
	}

	int TurnManager::getChangeTimer()
	{
		return changeTimer;
	}

	void TurnManager::setChangeTimer(int change)
	{
		changeTimer = change;
	}
	
	TurnManager::~TurnManager() {}

	TurnManager turnM;
}