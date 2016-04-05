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
void BulletManager::AddBullet(sf::Vector2f bulletHPos, static int bulletType)
{
	BulletHole* b = new BulletHole(bulletHPos, bulletType, &bulletMetalTexture);
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
	for (BulletHole* b: bulletHoles)
	{
		b->Draw(window);
	}
}

list<BulletHole*>& BulletManager::GetListOfBullets()
{
	return bulletHoles;
}