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
	list<Target*>& targets = TargetManager::GetInstance()->GetListOfTargets();
	list<Target*>::iterator targetITER = targets.begin();

	for (targetITER = targets.begin(); targetITER != targets.end(); ) 
	{
		if ((crosshairPos.x > (*targetITER)->GetPosition().x && crosshairPos.x < (*targetITER)->GetPosition().x + (*targetITER)->GetWidth()
			&& crosshairPos.y >(*targetITER)->GetPosition().y + 10 && crosshairPos.y < (*targetITER)->GetPosition().y + (*targetITER)->GetHeight()))
			{
				(*targetITER)->SetHealth();
				(*targetITER)->AddBullet(crosshairPos);
				if ((*targetITER)->GetHealth() <= 0)
				{
					delete (*targetITER);
					targetITER = targets.erase(targetITER);
				}
				return true;
			}
		else
		{
			++targetITER;
		}
	}
	return false;
}

bool CollisionManager::CheckReloadCollision(sf::Vector2f crosshairPos, sf::Vector2f reloadPos, sf::FloatRect reloadBounds)
{
	if ((crosshairPos.x > reloadPos.x && crosshairPos.x < reloadPos.x + reloadBounds.width
		&& crosshairPos.y > reloadPos.y && crosshairPos.y < reloadPos.y + reloadBounds.height))
	{
		return true;
	}
	return false;
}