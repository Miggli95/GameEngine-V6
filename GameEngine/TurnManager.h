#ifndef TURNMANAGER_H
#define TURNMANAGER_H
namespace GameEngine
{
	class TurnManager
	{
	public:
		TurnManager();
		void addPlayer();
		void removePlayer();
		int getPlayerID();
		int getCurrentPlayer();
		int getNumberOfPlayers();
		void Update();
		bool getChangePlayer();
		void setChangePlayer(bool change);
		void EndTurn();
		void ChangePlayerIDs();
		int getChangeTimer();
		void IncreaseChangeTimer(int to);
		void setChangeTimer(int change);
		~TurnManager();

	private:
		int numberOfPlayers = 0;
		int currentPlayer = 1;
		int changeTimer = 0;
		bool changePlayer = false;
	};
	extern TurnManager turnM;
}
#endif

