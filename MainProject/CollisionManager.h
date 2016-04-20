#include <iostream>
#include <list>

using namespace std;

#ifndef COLLISIONMANAGER
#define COLLISIONMANAGER

#include "TargetManager.h"
#include "BulletManager.h"
#include "LevelManager.h"

class CollisionManager
{
public:
	~CollisionManager()
	{
		delete instance;
		instanceFlag = false;
	}
	static CollisionManager* GetInstance();

	bool CollisionManager::CheckTargetCollision(sf::Vector2f, static int gunType);
	bool CollisionManager::CheckReloadCollision(sf::Vector2f, sf::Vector2f, sf::FloatRect);
	//void CollisionManager::SetBulletTargCollision(sf::Vector2f);
	//bool CollisionManager::CheckMenuElementCollision(sf::Vector2i crosshairPos, sf::Sprite &element);
	bool CollisionManager::CheckMenuElementCollision(sf::Vector2i crosshairPos, sf::Vector2f pos, sf::FloatRect bounds);
	void CollisionManager::CheckTargetColourCollision(sf::Vector2f bulletPos, list<Target*>::iterator targetITER);
	void CollisionManager::CheckHeadshotCollision(sf::Vector2f bulletPos, list<Target*>::iterator targetITER);

private:
	static bool instanceFlag;
	static CollisionManager* instance;

};

#endif