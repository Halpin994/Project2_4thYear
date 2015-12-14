#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>

#include "TargetManager.h"

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
void TargetManager::AddTargets(sf::Vector2f targetPos, float tHealth)
{
	Target t;
	t.SetUp(targetPos, &targetImage, tHealth);
	targets.push_back(t);
}



//! Draws the targets
/*!
\When called, the Draw() method iterates through the list of targets.
\It then calls upon the Draw() method inside the Target class to draw the bullets to the screen.
\return none
\sa
*/
void TargetManager::Draw(sf::RenderWindow& window)
{
	list<Target>::iterator it = targets.begin();
	for (it = targets.begin(); it != targets.end(); ++it)
	{
		if (it->GetHealth() > 0)
		{
			it->Draw(window);
		}
	}
}

list<Target>& TargetManager::GetListOfTargets()
{
	return targets;
}