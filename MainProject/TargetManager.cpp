#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>

#include "TargetManager.h"
#include "GameStateManager.h"
#include "Level.h"

bool TargetManager::instanceFlag = false;
TargetManager* TargetManager::instance = NULL;

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
TargetManager* TargetManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new TargetManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

//! Adds targets to a list
/*!
\This method is passed a vector2f position when called in the Level class SetUp() method
\the position is then used when calling the SetUp for the target class, it is also passed the address of targetImage
\as the SetUp requires a texture to be added to the sprite.
\return none
\sa
*/
void TargetManager::AddTargets(sf::Vector2f targetPos, float tHealth, int tLayer)
{
	Target* t = new Target();
	if (Level::GetInstance()->GetLevelState() == Level::GetInstance()->TUTORIAL)
	{
		t->SetUp(targetPos, &targetTexture, &bulletWoodTexture, tHealth, tLayer);
	}
	else if (Level::GetInstance()->GetLevelState() == Level::GetInstance()->LEVEL1)
	{
		t->SetUp(targetPos, &target2Texture, &bulletWoodTexture, tHealth, tLayer);
	}
	targets.push_back(t);
}



//! Draws the targets
/*!
\When called, the Draw() method iterates through the list of targets.
\It then calls upon the Draw() method inside the Target class to draw the bullets to the screen.
\return none
\sa
*/
void TargetManager::Draw(sf::RenderWindow& window, int layer)
{
	//list<Target>::iterator targetITER = targets.end();
	//for (targetITER = targets.end(); targetITER != targets.begin(); --targetITER)
	for (Target* t: targets)
	{
		if (t->GetLayer() == layer && t->GetTimeToLive() > 0)
		t->Draw(window);
	}
}

void TargetManager::Update(float ft)
{
	for (std::list<Target*>::iterator targetIter = targets.begin(), endIter = targets.end(); targetIter != endIter; )
	{
		//Pull the pointer from the iterator
		//Target* currentTarget = (*targetIter);

		//If we have a TTL, update
		if ((*targetIter)->GetTimeToLive() > 0)
		{
			(*targetIter)->Update(ft);

			//And then update the iterator here
			targetIter++;
		}
		else
		{
			//Delete target
			delete (*targetIter);

			//Update iterator by erasing
			targetIter = targets.erase(targetIter);
		}
	}
}

list<Target*>& TargetManager::GetListOfTargets()
{
	return targets;
}

int TargetManager::GetSizeOfTargets()
{
	return targets.size();
}

void TargetManager::targetsEliminatedPlus()
{
	targetsEliminated++;
	if (targetsEliminated == 6)
	{
		targetsEliminated = 0;
		GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::GAMEOVER);
	}
}