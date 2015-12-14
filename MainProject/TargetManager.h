#include <iostream>
#include <list>

using namespace std;

#ifndef TARGETMANAGER
#define TARGETMANAGER

#include "Target.h"

class TargetManager
{
public:
	~TargetManager()
	{
		delete instance;
		instanceFlag = false;
	}
	static TargetManager* GetInstance();

	void TargetManager::Draw(sf::RenderWindow& window);
	void TargetManager::AddTargets(sf::Vector2f targetPos, float);
	list<Target>& TargetManager::GetListOfTargets();

private:
	TargetManager()
	{
		targets = list<Target>();
		targetImage.loadFromFile("Assets/Images/Game/target.png");
	}
	static bool instanceFlag;
	static TargetManager* instance;
	sf::Texture targetImage;
	list<Target> targets;

};

#endif 