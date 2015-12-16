#include <iostream>
#include <list>

using namespace std;

#ifndef TARGETMANAGER
#define TARGETMANAGER

#include "Target.h"
#include "Player.h"

class TargetManager
{
public:
	~TargetManager()
	{
		delete instance;
		instanceFlag = false;
		for (Target* t : targets)
		{
			delete t;
		}
	}
	static TargetManager* GetInstance();

	void TargetManager::Draw(sf::RenderWindow& window);
	void TargetManager::AddTargets(sf::Vector2f targetPos, float);
	list<Target*>& TargetManager::GetListOfTargets();
	int TargetManager::GetSizeOfTargets();
	void TargetManager::targetsEliminatedPlus();

private:
	TargetManager()
	{
		targets = list<Target*>();
		targetTexture.loadFromFile("Assets/Images/Game/target.png");
		bulletWoodTexture.loadFromFile("Assets/Images/Game/bulletHole_wood.png");

		targetsEliminated = 0;
	}
	static bool instanceFlag;
	static TargetManager* instance;
	sf::Texture targetTexture;
	list<Target*> targets;

	sf::Texture bulletWoodTexture;

	int targetsEliminated;

};

#endif 