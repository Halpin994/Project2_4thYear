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

//! Adds bullets to a list
/*!
\When called, it is passed a bulletType and position when called in the Shoot() method in the bullet class
\the bulletType and position are passed from the Player class which holds the Shoot() method and determines these variables.
\return none
\sa
*/
void TargetManager::AddTargets(sf::Vector2f targetPos)
{
	Target t;
	t.SetUp(targetPos, &targetImage);
	targets.push_back(t);
}

//! Draws the bullet holes
/*!
\When called, the Draw() method iterates through the list of bullets.
\It then calls upon the Draw() method inside the BulletHole class to draw the bullets to the screen.
\return none
\sa
*/
void TargetManager::Draw(sf::RenderWindow& window)
{
	list<Target>::iterator it = targets.begin();
	for (it = targets.begin(); it != targets.end(); ++it)
	{
		it->Draw(window);
	}
}