#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "GameStateManager.h"

bool GameStateManager::instanceFlag = false;
GameStateManager* GameStateManager::instance = NULL;

//! GetInstance returns pointer to GameStateManager (singleton)
/*!
\(Detailed desc)
\return
\sa
*/
GameStateManager* GameStateManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new GameStateManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

//! Sets the game state
/*!
\When called, it is passed a gamestate, which sets the current game state to the state passed.
\return none
\sa 
*/
void GameStateManager::SetGameState(GameStates state)
{
	gameState = state;
}

//! Gets the game state
/*!
\When called, it returns the current gameState.
\return gameState
\sa
*/
GameStateManager::GameStates GameStateManager::GetGameState()
{
	return gameState;
}