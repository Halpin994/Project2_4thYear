#include <iostream>
using namespace std;

#ifndef GAMESTATEMANAGER
#define GAMESTATEMANAGER

class GameStateManager
{
public:
	~GameStateManager()
	{
		delete instance;
		instanceFlag = false;
	}

	static GameStateManager* GetInstance();

	enum class GameStates { MAIN_MENU, OPTIONS, GAME, GAMEOVER, QUIT };

	void SetGameState(GameStates);
	GameStates GetGameState();

private:
	GameStateManager()
	{

	}
	static bool instanceFlag;
	static GameStateManager* instance;

	GameStates gameState;

};
#endif 