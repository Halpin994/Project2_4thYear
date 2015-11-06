#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "GameStateManager.h"

bool GameStateManager::instanceFlag = false;
GameStateManager* GameStateManager::instance = NULL;



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


//! func desc brief
/*!
\param state desc of what state is
\return none
\sa 
*/
void GameStateManager::SetGameState(GameStates state)
{
	gameState = state;
}

GameStateManager::GameStates GameStateManager::GetGameState()
{
	return gameState;
}