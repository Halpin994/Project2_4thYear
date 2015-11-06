#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>

#include "BulletManager.h"

bool BulletManager::instanceFlag = false;
BulletManager* BulletManager::instance = NULL;

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

void BulletManager::AddBullets(int bulletType, sf::Vector2f bulletHPos)
{
	BulletHole b;
	b.SetUp(bulletType, bulletHPos, &bulletMetalImage,  &bulletWoodImage);
	bulletHoles.push_back(b);

}

void BulletManager::Draw(sf::RenderWindow& window)
{
	list<BulletHole>::iterator it = bulletHoles.begin();
	for (it = bulletHoles.begin(); it != bulletHoles.end(); ++it)
	{
		it->Draw(window);
	}
}