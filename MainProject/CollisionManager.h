#include <iostream>
#include <list>

using namespace std;

#ifndef COLLISIONMANAGER
#define COLLISIONMANAGER

#include "TargetManager.h"

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

private:
	static bool instanceFlag;
	static CollisionManager* instance;

};

#endif