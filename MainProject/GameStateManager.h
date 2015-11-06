#include <iostream>
using namespace std;

#ifndef GAMESTATEMANAGER
#define GAMESTATEMANAGER


//!  GetInstance returns pointer to GameStateManager (singleton) 
/*!
more detail here
and yet more
etc
*/
class GameStateManager
{
public:
	~GameStateManager()
	{
		delete instance;
		instanceFlag = false;
	}

	static GameStateManager* GetInstance();

	enum class GameStates { MAIN_MENU, GAME, OPTIONS, QUIT };

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