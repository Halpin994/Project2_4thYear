#include <iostream>
#include <list>

using namespace std;

#ifndef COLLISIONMANAGER
#define COLLISIONMANAGER

#include "TargetManager.h"
#include "BulletManager.h"

class CollisionManager
{
public:
	~CollisionManager()
	{
		delete instance;
		instanceFlag = false;
	}
	static CollisionManager* GetInstance();

	bool CollisionManager::CheckTargetCollision(sf::Vector2f);
	bool CollisionManager::CheckReloadCollision(sf::Vector2f, sf::Vector2f, sf::FloatRect);
	void CollisionManager::SetBulletTargCollision(sf::Vector2f);

private:
	static bool instanceFlag;
	static CollisionManager* instance;

};

#endif