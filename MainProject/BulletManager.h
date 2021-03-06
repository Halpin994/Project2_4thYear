#include <iostream>
#include <list>

using namespace std;

#ifndef BULLETMANAGER
#define BULLETMANAGER

#include "BulletHole.h"

class BulletManager
{
public:
	~BulletManager()
	{
		delete instance;
		instanceFlag = false;
		for (BulletHole* b : bulletHoles)
		{
			delete b;
		}
	}
	static BulletManager* GetInstance();

	void BulletManager::Draw(sf::RenderWindow& window);
	void BulletManager::AddBullet(sf::Vector2f, static int bulletType);
	list<BulletHole*>& BulletManager::GetListOfBullets();

private:
	BulletManager()
	{
		bulletHoles = list<BulletHole*>();
		bulletMetalTexture.loadFromFile("Assets/Images/Game/bulletHole_metal.png");
	}
	static bool instanceFlag;
	static BulletManager* instance;
	sf::Texture bulletMetalTexture;
	list<BulletHole*> bulletHoles;

};

#endif 