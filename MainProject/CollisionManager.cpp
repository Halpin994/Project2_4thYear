#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>

#include "CollisionManager.h"

bool CollisionManager::instanceFlag = false;
CollisionManager* CollisionManager::instance = NULL;

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
CollisionManager* CollisionManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new CollisionManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

bool CollisionManager::CheckTargetCollision(sf::Vector2f crosshairPos)
{
	list<Target> targets = TargetManager::GetInstance()->GetListOfTargets();
	list<Target>::iterator it = targets.begin();
	for (it = targets.begin(); it != targets.end(); ++it)
	{
		if ((crosshairPos.x > it->GetPosition().x && crosshairPos.x < it->GetPosition().x + it->GetWidth()
			&& crosshairPos.y > it->GetPosition().y + 10 && crosshairPos.y < it->GetPosition().y + it->GetHeight()))
		{
			//cout << "Target Hit" << endl;
			return true;
		}
	}
	return false;

	/*for each (Target t in TargetManager::GetInstance()->GetListOfTargets())
	{
		t.GetPosition();
	}*/
}