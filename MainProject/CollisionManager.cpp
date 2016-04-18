#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>

#include "CollisionManager.h"
#include "Player.h"
#include "ScoreManager.h"
#include "SoundManager.h"

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

bool CollisionManager::CheckTargetCollision(sf::Vector2f bulletPos, static int gunType)
{
	list<Target*>& targets = LevelManager::GetInstance()->GetCurrentLevel()->GetListOfTargets();
	list<Target*>::iterator targetITER = targets.begin();

	for (targetITER = targets.begin(); targetITER != targets.end(); )
	{
		if ((*targetITER)->GetGlobalBounds().contains(bulletPos))
			{
				(*targetITER)->SetHealth();
				(*targetITER)->AddBullet(bulletPos, gunType);
				CheckTargetColourCollision(bulletPos, targetITER);
				//if ((*targetITER)->GetHealth() <= 0)
				//{
				//	TargetManager::GetInstance()->targetsEliminatedPlus();
				//	delete (*targetITER);
				//	targetITER = targets.erase(targetITER);
				//}
				return true;
			}
		else
		{
			++targetITER;
		}
	}
	return false;
}

void CollisionManager::CheckTargetColourCollision(sf::Vector2f bulletPos, list<Target*>::iterator targetITER)
{
	float distanceBotTarg = sqrtf(
		powf(bulletPos.x - ((*targetITER)->GetPosition().x + ((*targetITER)->GetWidth() / 2)), 2)
		+ 
		powf(bulletPos.y - ((*targetITER)->GetPosition().y + ((*targetITER)->GetHeight() / (170.0f / 111.0f))), 2)
		);
	float distanceTopTarg = sqrtf(
		powf(bulletPos.x - ((*targetITER)->GetPosition().x + ((*targetITER)->GetWidth() / 2)), 2)
		+
		powf(bulletPos.y - ((*targetITER)->GetPosition().y + ((*targetITER)->GetHeight() / (170.0f / 53.0f))), 2)
		);

	if (distanceBotTarg <= ((*targetITER)->GetWidth() / 2) / (50.0f / 30.0f))
	{
		if (distanceBotTarg <= ((*targetITER)->GetWidth() / 2) / (50.0f / 7.0f))
		{
			SoundManager::GetInstance()->PlayMetalClangSoundEffect();
			ScoreManager::GetInstance()->AddScore(25, bulletPos, "yellow", "bottom");
		}
		else if (distanceBotTarg <= ((*targetITER)->GetWidth() / 2) / (50.0f / 14.0f))
		{
			SoundManager::GetInstance()->PlayWoodClangSoundEffect();
			ScoreManager::GetInstance()->AddScore(20, bulletPos, "red", "bottom");
		}
		else if (distanceBotTarg <= ((*targetITER)->GetWidth() / 2) / (50.0f / 21.0f))
		{
			SoundManager::GetInstance()->PlayWoodClangSoundEffect();
			ScoreManager::GetInstance()->AddScore(15, bulletPos, "blue", "bottom");
		}
		else //if (distance <= ((*targetITER)->GetWidth() / 2) / (50.0f / 30.0f))
		{
			SoundManager::GetInstance()->PlayWoodClangSoundEffect();
			ScoreManager::GetInstance()->AddScore(10, bulletPos, "white", "bottom");
		}
	}
	else if (distanceTopTarg <= ((*targetITER)->GetWidth() / 2) / (50.0f / 14.0f))
	{
		if (distanceTopTarg <= ((*targetITER)->GetWidth() / 2) / (50.0f / 3.0f))
		{
			SoundManager::GetInstance()->PlayMetalClangSoundEffect();
			ScoreManager::GetInstance()->AddScore(50, bulletPos, "yellow", "top");
		}
		else if (distanceTopTarg <= ((*targetITER)->GetWidth() / 2) / (50.0f / 6.0f))
		{
			SoundManager::GetInstance()->PlayWoodClangSoundEffect();
			ScoreManager::GetInstance()->AddScore(40, bulletPos, "red", "top");
		}
		else if (distanceTopTarg <= ((*targetITER)->GetWidth() / 2) / (50.0f / 10.0f))
		{
			SoundManager::GetInstance()->PlayWoodClangSoundEffect();
			ScoreManager::GetInstance()->AddScore(25, bulletPos, "blue", "top");
		}
		else //if (distance <= ((*targetITER)->GetWidth() / 2) / (50.0f / 30.0f))
		{
			SoundManager::GetInstance()->PlayWoodClangSoundEffect();
			ScoreManager::GetInstance()->AddScore(20, bulletPos, "white", "top");
		}
	}
	else
		SoundManager::GetInstance()->PlayWoodClangSoundEffect();


}