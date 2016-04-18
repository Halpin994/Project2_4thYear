#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "Level.h"
#include "TargetManager.h"
#include "SoundManager.h"
#include "BulletManager.h"
#include "ScoreManager.h"
#include "Player.h"

//bool Level::instanceFlag = false;
//Level* Level::instance = NULL;
//
//Level* Level::GetInstance()
//{
//	if (!instanceFlag)
//	{
//		instance = new Level;
//		instanceFlag = true;
//		return instance;
//	}
//	else
//	{
//		return instance;
//	}
//}

//! Default Constructor
/*!
\When called, this sets its self up through calling the load and set up functions
\return none
\sa
*/
Level::Level(string lvl)
{
	gameTime = 0;
	gameOverTime = 10.0f;
	list<Target*> targets = list<Target*>();
	Load();
	SetUp();
	currentLevel = lvl;
	levelEnd = false;
	player = new Player();

	//gameOverTime = 0;
}

//! Load in assets
/*!
\Loads in the background image and assigns it to texture rangeImage
\return none
\sa
*/
void Level::Load()
{
	//shootInfoTexture.loadFromFile("Assets/Images/Game/Tutorial/tut_shoot.png");
	//reloadInfoTexture.loadFromFile("Assets/Images/Game/Tutorial/tut_reload.png");
	//quickReloadTexture.loadFromFile("Assets/Images/Game/Tutorial/tut_quickreload.png");

	statsTexture.loadFromFile("Assets/Images/Game/statsBG.png");

	font.loadFromFile("Assets/imagine_font.ttf");
}

//! Setup the level's range sprite
/*!
\Set the sprites texture to the rangeImage loaded in the load() function.
\return none
\sa
*/
void Level::SetUp()
{
	//if (levelState == LevelStates::LEVEL1)
	//{
	//	bgSprite.setTexture(rangeBgTexture, true);
	//	TargetManager::GetInstance()->AddTargets(sf::Vector2f(395, 180), 100, 0);
	//	TargetManager::GetInstance()->AddTargets(sf::Vector2f(600, 180), 10000, 0);
	//	TargetManager::GetInstance()->AddTargets(sf::Vector2f(810, 180), 100, 0);
	//}

	//if (levelState == LevelStates::LEVEL2)
	//{
	//	spr_level1Layer1.setTexture(texture_level1Layer1);
	//	spr_level1Layer2.setTexture(texture_level1Layer2);
	//	spr_level1Layer3.setTexture(texture_level1Layer3);
	//	spr_level1Layer4.setTexture(texture_level1Layer4);

	//	//Right side building
	//	TargetManager::GetInstance()->AddTargets(sf::Vector2f(840, 200), 100, 1);
	//	TargetManager::GetInstance()->AddTargets(sf::Vector2f(790, 200), 100, 1);
	//	//Right side building

	//	//Back sandbags
	//	TargetManager::GetInstance()->AddTargets(sf::Vector2f(395, 240), 100, 1);
	//	//Back sandbags

	//	//Left fake building
	//	TargetManager::GetInstance()->AddTargets(sf::Vector2f(220, 240), 100, 1);
	//	//Left fake building

	//	//Foreground rock
	//	TargetManager::GetInstance()->AddTargets(sf::Vector2f(600, 380), 100, 2);
	//	//Foreground rock

	//	//Foreground sandbags
	//	TargetManager::GetInstance()->AddTargets(sf::Vector2f(810, 300), 100, 3);
	//	//Foreground sandbags
	//}

	statsSprite.setTexture(statsTexture);
	statsSprite.setPosition(sf::Vector2f(0, 0));

	gameTimeText.setFont(font);
	gameTimeText.setCharacterSize(50);
	gameTimeText.setPosition(900, 635);
	gameTimeText.setColor(sf::Color::Yellow);

	frameRateText.setFont(font);
	frameRateText.setCharacterSize(18);
	frameRateText.setPosition(10, 0);
	frameRateText.setColor(sf::Color::Yellow);

	frameNum = 1;
}

//! Draw the level
/*!
\Draw the level range sprite relative to the window
\return none
\sa
*/
void Level::DrawLayer(sf::RenderWindow& window, int layer)
{
	for (std::list<std::pair<sf::Sprite, int>>::iterator iter = levelSprites.begin(), end = levelSprites.end(); iter != end; iter++)
	{
		if (iter->second == layer)
		{
			window.draw(iter->first);
		}
	}

	TargetManager::GetInstance()->Draw(window, layer, targets);

	

	//if (levelState == LevelStates::LEVEL1)
	//{
	//	window.draw(bgSprite);
	//	BulletManager::GetInstance()->Draw(window);
	//	TargetManager::GetInstance()->Draw(window, 0);
	//}
	//else if (levelState == LevelStates::LEVEL2)
	//{
	//	window.draw(bgSprite);

	//	window.draw(spr_level1Layer1);
	//	//Draw enemies behind the buildings and in the watch tower here
	//	TargetManager::GetInstance()->Draw(window, 1);
	//	window.draw(spr_level1Layer2);
	//	//Draw enemies behind the stones here
	//	TargetManager::GetInstance()->Draw(window, 2);
	//	window.draw(spr_level1Layer3);
	//	//Draw enemies behind the foreground sandbags here
	//	TargetManager::GetInstance()->Draw(window, 3);
	//	window.draw(spr_level1Layer4);

	//	BulletManager::GetInstance()->Draw(window);
	//	//TargetManager::GetInstance()->Draw(window);
	//}
}

void Level::Draw(sf::RenderWindow& window)
{
	player->Draw(window);
}

void Level::DrawOverlayUI(sf::RenderWindow& window)
{
	ss.str(std::string());
	float gt = gameTime;
	gt = roundf(gt * 100) / 100;
	ss << gt;
	gameTimeText.setString(ss.str());
	window.draw(gameTimeText);

	ss.str(std::string());
	float fr = frameRate;
	fr = roundf(fr * 1) / 1; //replace 1 with 1000 and game time will be rounded to three decimal places
	ss << fr;
	frameRateText.setString(ss.str());
	window.draw(frameRateText);

	ScoreManager::GetInstance()->Draw(window);
	
	//if (levelState == LevelStates::LEVEL1)
	//{
	//	if (tut_ShootInfoDraw == true)
	//	{
	//		window.draw(infoSprite);
	//	}
	//	if (tut_ReloadInfoDraw == true)
	//	{
	//		window.draw(infoSprite);
	//	}
	//	if (tut_QuickReloadDraw == true)
	//	{
	//		window.draw(infoSprite);
	//	}
	//}
}

void Level::Update(double frameTime, sf::RenderWindow& window)
{
	gameTime += frameTime;

	if (frameNum <= 100)
	{
		frameRateSum += frameTime;
		if (frameNum == 100)
		{
			
			frameRate = 1.0f / (frameRateSum / 100.0f);
			frameNum = 0;
			frameRateSum = 0;
		}
		frameNum++;
	}

	ScoreManager::GetInstance()->Update(frameTime, player);
	TargetManager::GetInstance()->Update(frameTime, &targets);
	player->Update(window, frameTime);
	SoundManager::GetInstance()->Update();
}

void Level::AddTarget(sf::Vector2f pos, sf::Texture* targetImage, sf::Texture* bulletImage, float health, int layer)
{
	Target* t = new Target();
	t->SetUp(pos, targetImage, bulletImage, health, layer);
	targets.push_back(t);
}

void Level::AddLevelSprite(sf::Texture* levelImage, int layer, sf::Vector2f position)
{
	sf::Sprite s;
	s.setTexture(*levelImage);
	s.setPosition(position);
	levelSprites.push_back(std::make_pair(s, layer));
}

list<Target*> Level::GetListOfTargets()
{
	return targets;
}

bool Level::CheckEndState()
{
	if (currentLevel == "Highscore" && gameTime >= gameOverTime)
	{
		levelEnd = true;
	}
	else if (currentLevel == "Highspeed" && targets.size() == 0)
	{
		levelEnd = true;
	}
	else if (currentLevel == "Headshots")
	{
		levelEnd = true;
	}
	return levelEnd;
}

void Level::DrawResult(sf::RenderWindow& window)
{
	window.draw(statsSprite);

	//sf::Text buttonText;
	//buttonText.setString("Press R to restart the level \n\nPress C to continue to level 2");
	//buttonText.setPosition(50, 100);

	//buttonText.setFont(font);
	//buttonText.setCharacterSize(50);
	//buttonText.setColor(sf::Color::White);


	//ss.str(std::string());
	//gameTime = roundf(gameTime * 100) / 100;
	//ss << gameTime;
	//string txt = "You shot 6 targets in: ";
	//gameTimeText.setString(txt + ss.str() + " seconds");
	//gameTimeText.setPosition(50, 600);

	//window.draw(gameTimeText);
	//window.draw(buttonText);
}

void Level::Restart()
{
	gameTime = 0;
	gameTimeText.setPosition(900, 635);
	targetRespawn = targetRespawnTime;

	list<BulletHole*>& bulletHoles = BulletManager::GetInstance()->GetListOfBullets();
	list<BulletHole*>::iterator bulletITER = bulletHoles.begin();
	for (bulletITER = bulletHoles.begin(); bulletITER != bulletHoles.end();)
	{
		delete (*bulletITER);
		bulletITER = bulletHoles.erase(bulletITER);
	}
	//if (levelState == LevelStates::TUTORIAL)
	//{
	//	TargetManager::GetInstance()->AddTargets(sf::Vector2f(395, 180), 100, 0);
	//	TargetManager::GetInstance()->AddTargets(sf::Vector2f(600, 180), 100, 0);
	//	TargetManager::GetInstance()->AddTargets(sf::Vector2f(810, 180), 100, 0);
	//}
	SetUp();
}

//void Level::UpdateTut(Player *player, float frameTime)
//{
//	if (player->getLeftClicked())
//	{
//		tut_ShootInfoDraw = false;
//	}
//	if (player->getNormReloadClicked())
//	{
//		tut_ReloadInfoDraw = false;
//	}
//	if (player->getQuickReloadClicked())
//	{
//		tut_QuickReloadDraw = false;
//	}
//
//	if (tut_ShootInfoDisplayed == false && gameTime > 1.0f)
//	{
//		tut_ShootInfoDraw = true;
//		tut_ShootInfoDisplayed = true;
//		infoSprite.setTexture(shootInfoTexture, true);
//		SoundManager::GetInstance()->PlayInfoSoundEffect();
//		infoSprite.setPosition(750, 460);
//	}
//	if (tut_ReloadInfoDisplayed == false && player->getClipCount() < player->getMaxClip() / 2 && tut_ShootInfoDraw == false && tut_QuickReloadDraw == false)
//	{
//		tut_ReloadInfoDraw = true;
//		tut_ReloadInfoDisplayed = true;
//		infoSprite.setTexture(reloadInfoTexture, true);
//		SoundManager::GetInstance()->PlayInfoSoundEffect();
//		infoSprite.setPosition(475, 460);
//	}
//	if (tut_QuickReloadDisplayed == false && player->getClipCount() <= 3 && tut_ShootInfoDraw == false && tut_ReloadInfoDraw == false && player->getNormReloadClicked() == false)
//	{
//		tut_QuickReloadDraw = true;
//		tut_QuickReloadDisplayed = true;
//		infoSprite.setTexture(quickReloadTexture, true);
//		SoundManager::GetInstance()->PlayInfoSoundEffect();
//		//infoSprite.setPosition(475, 460);
//	}
//
//	if (tut_ShootInfoDraw == true || tut_ReloadInfoDraw == true || tut_QuickReloadDraw == true)
//	{
//		tut_displayTimer += frameTime;
//	}
//}

string Level::GetLevelType()
{
	return currentLevel;
}