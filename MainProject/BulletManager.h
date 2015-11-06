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
	}
	static BulletManager* GetInstance();

	void BulletManager::Draw(sf::RenderWindow& window);
	void BulletManager::AddBullets(int, sf::Vector2f);

private:
	BulletManager()
	{
		bulletHoles = list<BulletHole>();
		bulletMetalImage.loadFromFile("bulletHole_metal.png");
		bulletWoodImage.loadFromFile("bulletHole_wood.png");
	}
	static bool instanceFlag;
	static BulletManager* instance;
	sf::Texture bulletMetalImage;
	sf::Texture bulletWoodImage;
	list<BulletHole> bulletHoles;

};

#endif 