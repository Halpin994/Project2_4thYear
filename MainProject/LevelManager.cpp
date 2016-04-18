#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>
#include <string>
#include <iostream>
#include "LevelManager.h"
#include "GameStateManager.h"
#include "TargetManager.h"
#include "BulletManager.h"
#include "SoundManager.h"
#include "Level.h"
#include "Menu.h"

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

LevelManager::LevelManager()
{

}

void LevelManager::CreateLevel(string lvl)
{
	numOfTotalShots = 0;
	topTargYellowHits = 0;
	topTargRedHits = 0;
	topTargBlueHits = 0;
	topTargWhiteHits = 0;
	bottomTargYellowHits = 0;
	bottomTargRedHits = 0;
	bottomTargBlueHits = 0;
	bottomTargWhiteHits = 0;
	delete level;

	if (lvl == "Level1-Highscore")
	{
		currentLevel = 1;
		targetImage.loadFromFile("Assets/Images/Game/target.png");
		bulletImage.loadFromFile("Assets/Images/Game/bulletHole_wood.png");
		level = new Level("Highscore");
		level->AddTarget(sf::Vector2f(395, 180), &targetImage, &bulletImage, 100, 1);
		level->AddTarget(sf::Vector2f(600, 180), &targetImage, &bulletImage, 100, 1);
		level->AddTarget(sf::Vector2f(810, 180), &targetImage, &bulletImage, 100, 1);

		layer0_Image.loadFromFile("Assets/Images/Game/basicRange.png");
		level->AddLevelSprite(&layer0_Image, 0, sf::Vector2f(0, 0));

		gameOverTime = 15.0f;
		targRespawnTime = 0.5;
		levelEnd = false;
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

		levelEnd = false;
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

		levelEnd = false;
	}
}

void LevelManager::Draw(sf::RenderWindow& window)
{
	if (CheckEndState() == true)
	{
		level->DrawLayer(window, 0);
		level->DrawLayer(window, 1);
		level->DrawLayer(window, 2);
		level->DrawLayer(window, 3);
		level->DrawLayer(window, 4);
		level->Draw(window);
		level->DrawResult(window);
	}
	else
	{
		level->DrawLayer(window, 0);
		level->DrawLayer(window, 1);
		level->DrawLayer(window, 2);
		level->DrawLayer(window, 3);
		level->DrawLayer(window, 4);
		BulletManager::GetInstance()->Draw(window);
		level->Draw(window);
		level->DrawOverlayUI(window);
	}

}

void LevelManager::Update(float time, sf::RenderWindow& window)
{
	if (CheckEndState() == true)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::MAIN_MENU);
		}
	}
	else
	{
		level->Update(time, window);
		CheckEndState();
	}

	if (level->GetLevelType() == sf::String("Highscore") && currentLevel == 1)
	{
		if (level->GetListOfTargets().size() == 0)
		{
			targRespawnTime -= time;
			if (targRespawnTime < 0)
			{
				SoundManager::GetInstance()->PlayClick();
				level->AddTarget(sf::Vector2f(395, 180), &targetImage, &bulletImage, 100, 1);
				level->AddTarget(sf::Vector2f(600, 180), &targetImage, &bulletImage, 100, 1);
				level->AddTarget(sf::Vector2f(810, 180), &targetImage, &bulletImage, 100, 1);
				targRespawnTime = 0.5;
			}
		}
	}

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

bool LevelManager::CheckEndState()
{
	if (levelEnd == false)
	{
		if (level->GetLevelType() == sf::String("Highscore") && level->GetLevelTime() >= gameOverTime)
		{
			levelEnd = true;
			level->AddStatText("Accuracy");
			level->AddStatText("Score");
			SoundManager::GetInstance()->PlayClick();
		}
		else if (level->GetLevelType() == sf::String("Highspeed") && level->GetListOfTargets().size() == 0)
		{
			levelEnd = true;
		}
		else if (level->GetLevelType() == sf::String("Headshots"))
		{
			levelEnd = true;
		}
	}
	return levelEnd;
}

Level* LevelManager::GetCurrentLevel()
{
	return level;
}

void LevelManager::AddShotFired(sf::String location)
{
	numOfTotalShots += 1;
	if (location == sf::String("topYellow"))
	{
		topTargYellowHits += 1;
	}
	if (location == sf::String("topRed"))
	{
		topTargRedHits += 1;
	}
	if (location == sf::String("topBlue"))
	{
		topTargBlueHits += 1;
	}
	if (location == sf::String("topWhite"))
	{
		topTargWhiteHits += 1;
	}
	if (location == sf::String("botYellow"))
	{
		bottomTargYellowHits += 1;
	}
	if (location == sf::String("botRed"))
	{
		bottomTargRedHits += 1;
	}
	if (location == sf::String("botBlue"))
	{
		bottomTargBlueHits += 1;
	}
	if (location == sf::String("botWhite"))
	{
		bottomTargWhiteHits += 1;
	}
}

float LevelManager::GetAccuracy()
{
	Accuracy = 0;
	if (numOfTotalShots != 0)
	{
		Accuracy =
			(
			(topTargYellowHits * 1.0f)
			+
			(topTargRedHits * 0.9f)
			+
			(topTargBlueHits * 0.8)
			+
			(topTargWhiteHits * 0.7)
			+
			(bottomTargYellowHits * 0.75)
			+
			(bottomTargRedHits * 0.7)
			+
			(bottomTargBlueHits * 0.6)
			+
			(bottomTargWhiteHits * 0.4)
			)
			/
			numOfTotalShots * 100;
	}
	if (Accuracy < 50)
	{
		if (!Menu::crapShot->unlocked)
		{
			Menu::crapShot->unlocked = true;
		}
	}
	else if (Accuracy > 90)
	{
		if (!Menu::crackShot->unlocked)
		{
			Menu::crackShot->unlocked = true;
		}
	}
	return Accuracy;
}

