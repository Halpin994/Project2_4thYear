#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>

#include "BulletManager.h"

bool BulletManager::instanceFlag = false;
BulletManager* BulletManager::instance = NULL;

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
BulletManager* BulletManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new BulletManager;
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
void BulletManager::AddBullets(int bulletType, sf::Vector2f bulletHPos)
{
	BulletHole b;
	b.SetUp(bulletType, bulletHPos, &bulletMetalTexture,  &bulletWoodTexture);
	bulletHoles.push_back(b);
}

//! Draws the bullet holes
/*!
\When called, the Draw() method iterates through the list of bullets.
\It then calls upon the Draw() method inside the BulletHole class to draw the bullets to the screen.
\return none
\sa
*/
void BulletManager::Draw(sf::RenderWindow& window)
{
	list<BulletHole>::iterator it = bulletHoles.begin();
	for (it = bulletHoles.begin(); it != bulletHoles.end(); ++it)
	{
		it->Draw(window);
	}
}