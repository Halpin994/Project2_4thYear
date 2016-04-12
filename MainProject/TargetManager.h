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
		//for (Target* t : targets)
		//{
		//	delete t;
		//}
	}
	static TargetManager* GetInstance();

	void TargetManager::Draw(sf::RenderWindow& window, int, list<Target*> targets);
	void TargetManager::AddTargets(sf::Vector2f targetPos, float tHealth, int tLayer);
	list<Target*>& TargetManager::GetListOfTargets();
	int TargetManager::GetSizeOfTargets();
	void TargetManager::targetsEliminatedPlus();
	void TargetManager::Update(float ft, list<Target*>* targets);

private:
	TargetManager()
	{
		//targets = list<Target*>();
		//targetTexture.loadFromFile("Assets/Images/Game/target.png");
		//target2Texture.loadFromFile("Assets/Images/Game/target2.png");
		//bulletWoodTexture.loadFromFile("Assets/Images/Game/bulletHole_wood.png");

		targetsEliminated = 0;
	}

	static bool instanceFlag;
	static TargetManager* instance;


	//sf::Texture targetTexture;
	//sf::Texture target2Texture;
	//list<Target*> targets;

	//sf::Texture bulletWoodTexture;

	int targetsEliminated;

};

#endif 