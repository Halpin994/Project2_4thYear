#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>
#include <string>
#include <iostream>
#include "LevelManager.h"
#include "TargetManager.h"
#include "BulletManager.h"
#include "Level.h"

bool LevelManager::instanceFlag = false;
LevelManager* LevelManager::instance = NULL;

LevelManager* LevelManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new LevelManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

LevelManager::LevelManager(){}

void LevelManager::CreateLevel(string lvl)
{
	if (lvl == "Level1-Highscore")
	{
		targetImage.loadFromFile("Assets/Images/Game/target.png");
		bulletImage.loadFromFile("Assets/Images/Game/bulletHole_wood.png");
		delete level;
		level = new Level("Highscore");
		level->AddTarget(sf::Vector2f(395, 180), &targetImage, &bulletImage, 100, 1);
		level->AddTarget(sf::Vector2f(600, 180), &targetImage, &bulletImage, 100, 1);
		level->AddTarget(sf::Vector2f(810, 180), &targetImage, &bulletImage, 100, 1);

		layer0_Image.loadFromFile("Assets/Images/Game/basicRange.png");
		level->AddLevelSprite(&layer0_Image, 0, sf::Vector2f(0, 0));
	}
	if (lvl == "Level1-Highspeed")
	{
		targetImage.loadFromFile("Assets/Images/Game/target.png");
		bulletImage.loadFromFile("Assets/Images/Game/bulletHole_wood.png");
		delete level;
		level = new Level("Highspeed");
		level->AddTarget(sf::Vector2f(395, 180), &targetImage, &bulletImage, 100, 1);
		level->AddTarget(sf::Vector2f(600, 180), &targetImage, &bulletImage, 100, 1);
		level->AddTarget(sf::Vector2f(810, 180), &targetImage, &bulletImage, 100, 1);

		layer0_Image.loadFromFile("Assets/Images/Game/basicRange.png");
		level->AddLevelSprite(&layer0_Image, 0, sf::Vector2f(0, 0));
	}

	else if (lvl == "Level2")
	{
		targetImage.loadFromFile("Assets/Images/Game/target2.png");
		bulletImage.loadFromFile("Assets/Images/Game/bulletHole_wood.png");
		delete level;
		level = new Level(lvl);

		//Right side building
		level->AddTarget(sf::Vector2f(840, 200), &targetImage, &bulletImage, 100, 1);
		level->AddTarget(sf::Vector2f(790, 200), &targetImage, &bulletImage, 100, 1);

		//Back sandbags
		level->AddTarget(sf::Vector2f(395, 240), &targetImage, &bulletImage, 100, 1);

		//Left fake building
		level->AddTarget(sf::Vector2f(220, 240), &targetImage, &bulletImage, 100, 1);

		//Foreground rock
		level->AddTarget(sf::Vector2f(600, 380), &targetImage, &bulletImage, 100, 2);

		//Foreground sandbags
		level->AddTarget(sf::Vector2f(810, 300), &targetImage, &bulletImage, 100, 3);

		layer0_Image.loadFromFile("Assets/Images/Game/Level 2/lvl2_bg.png");
		level->AddLevelSprite(&layer0_Image, 0, sf::Vector2f(0, 0));

		layer1_Image.loadFromFile("Assets/Images/Game/Level 2/lvl2_buildings_back.png");
		level->AddLevelSprite(&layer1_Image, 1, sf::Vector2f(0, 0));

		layer2_Image.loadFromFile("Assets/Images/Game/Level 2/lvl2_buildings_front.png");
		level->AddLevelSprite(&layer2_Image, 2, sf::Vector2f(0, 0));

		//layer3_Image.loadFromFile("Assets/Images/Game/Level 2/lvl2_twoStones.png");
		//level->AddLevelSprite(&layer3_Image, 3, sf::Vector2f(0, 0));

		layer4_Image.loadFromFile("Assets/Images/Game/Level 2/lvl2_foreground_sandbags.png");
		level->AddLevelSprite(&layer4_Image, 4, sf::Vector2f(0, 0));
	}
}

void LevelManager::Draw(sf::RenderWindow& window)
{
	level->Draw(window, 0);
	level->Draw(window, 1);
	level->Draw(window, 2);
	level->Draw(window, 3);
	level->Draw(window, 4);
	BulletManager::GetInstance()->Draw(window);
	level->DrawOverlayUI(window);
}

void LevelManager::Update(Player* player, float time)
{
	level->Update(player, time);
	level->CheckEndState();

	//if (GetCurrentLevel()->GetLevelType() == "Level1-Highscore")
	//{
	//	if (TargetManager::GetInstance()->GetSizeOfTargets() == 0)
	//	{
	//		targetRespawn -= frameTime;
	//		if (targetRespawn < 0)
	//		{
	//			AddTarget(sf::Vector2f(395, 180), &targetImage, &bulletImage, 100, 1);
	//			AddTarget(sf::Vector2f(600, 180), &targetImage, &bulletImage, 100, 1);
	//			AddTarget(sf::Vector2f(810, 180), &targetImage, &bulletImage, 100, 1);
	//			SoundManager::GetInstance()->PlayClick();
	//			targetRespawn = targetRespawnTime;
	//		}
	//	}
	//}
}

Level* LevelManager::GetCurrentLevel()
{
	return level;
}