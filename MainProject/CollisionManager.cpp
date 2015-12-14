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
	list<BulletHole>& bulletHoles = BulletManager::GetInstance()->GetListOfBulletHoles();
	list<BulletHole>::iterator bulletHoleITER = bulletHoles.begin();

	list<Target>& targets = TargetManager::GetInstance()->GetListOfTargets();
	list<Target>::iterator targetITER = targets.begin();
	//int targetNum = 0;

	for (targetITER = targets.begin(); targetITER != targets.end(); ++targetITER) 
	{
		//targetNum++;
		//for (bulletHoleITER = bulletHoles.begin(); bulletHoleITER != bulletHoles.end(); ++bulletHoleITER)
		//{
			if ((crosshairPos.x > targetITER->GetPosition().x && crosshairPos.x < targetITER->GetPosition().x + targetITER->GetWidth()
				&& crosshairPos.y > targetITER->GetPosition().y + 10 && crosshairPos.y < targetITER->GetPosition().y + targetITER->GetHeight()))
			{
				//bulletHoleITER->setTargetCollision(targetNum);
				targetITER->SetHealth();
				return true;
			}
		//}
	}
	//targetNum = 0;
	//bulletHoleITER->setTargetCollision(targetNum);
	return false;
}

void CollisionManager::SetBulletTargCollision(sf::Vector2f crosshairPos)
{
	list<BulletHole>& bulletHoles = BulletManager::GetInstance()->GetListOfBulletHoles();
	list<BulletHole>::iterator bulletHoleITER = bulletHoles.begin();

	list<Target>& targets = TargetManager::GetInstance()->GetListOfTargets();
	list<Target>::iterator targetITER = targets.begin();
	int targetNum = 0;

	for (targetITER = targets.begin(); targetITER != targets.end(); ++targetITER)
	{
		targetNum++;
		for (bulletHoleITER = bulletHoles.begin(); bulletHoleITER != bulletHoles.end(); ++bulletHoleITER)
		{
			if ((crosshairPos.x > targetITER->GetPosition().x && crosshairPos.x < targetITER->GetPosition().x + targetITER->GetWidth()
				&& crosshairPos.y > targetITER->GetPosition().y + 10 && crosshairPos.y < targetITER->GetPosition().y + targetITER->GetHeight()))
			{
				bulletHoleITER->SetBulletTargetCollision(targetNum);
				return;
			}
		}
	}
	targetNum = 0;
	bulletHoleITER->SetBulletTargetCollision(targetNum);
	return;
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