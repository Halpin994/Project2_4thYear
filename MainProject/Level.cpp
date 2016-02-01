#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "Level.h"
#include "TargetManager.h"
#include "SoundManager.h"
#include "BulletManager.h"

//! Default Constructor
/*!
\When called, this sets its self up through calling the load and set up functions
\return none
\sa
*/
Level::Level()
{
	Load();
	SetUp();

	tut_ShootInfoDisplayed = false;
	tut_ReloadInfoDisplayed = false;
	tut_QuickReloadDisplayed = false;

	tut_ShootInfoDraw = false;
	tut_ReloadInfoDraw = false;
	tut_QuickReloadDraw = false;

	tut_displayTime = 4.0f;
	tut_displayTimer = 0;

	gameTime = 0;
	gameOverTime = 0;

	targetRespawnTime = 0.4;
	targetRespawn = targetRespawnTime;
}

//! Load in assets
/*!
\Loads in the background image and assigns it to texture rangeImage
\return none
\sa
*/
void Level::Load()
{
	rangeTexture.loadFromFile("Assets/Images/Game/basicRange.png");
	shootInfoTexture.loadFromFile("Assets/Images/Game/Tutorial/tut_shoot.png");
	reloadInfoTexture.loadFromFile("Assets/Images/Game/Tutorial/tut_reload.png");
	quickReloadTexture.loadFromFile("Assets/Images/Game/Tutorial/tut_quickreload.png");

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
	rangeSprite.setTexture(rangeTexture, true);
	//infoSprite.setTexture(shootInfoTexture, true);
	infoSprite.setPosition(750, 460);
	TargetManager::GetInstance()->AddTargets(sf::Vector2f(395, 180), 100);
	TargetManager::GetInstance()->AddTargets(sf::Vector2f(600, 180), 100);
	TargetManager::GetInstance()->AddTargets(sf::Vector2f(810, 180), 100);

	gameTimeText.setFont(font);
	gameTimeText.setCharacterSize(50);
	gameTimeText.setPosition(900, 635);
	gameTimeText.setColor(sf::Color::Yellow);
}

//! Draw the level
/*!
\Draw the level range sprite relative to the window
\return none
\sa
*/
void Level::Draw(sf::RenderWindow& window)
{
	//rangeSprite.setPosition(0, 0);
	window.draw(rangeSprite);

	ss.str(std::string());
	gameTime = roundf(gameTime * 100) / 100;
	ss << gameTime;
	gameTimeText.setString(ss.str());
	window.draw(gameTimeText);

	if (tut_ShootInfoDraw == true)
	{
		window.draw(infoSprite);
	}
	if (tut_ReloadInfoDraw == true)
	{
		window.draw(infoSprite);
	}
	if (tut_QuickReloadDraw == true)
	{
		window.draw(infoSprite);
	}
}

void Level::Update(Player *player, float frameTime)
{
	gameTime += frameTime;
	

	if (TargetManager::GetInstance()->GetSizeOfTargets() == 0)
	{
		targetRespawn -= frameTime;
		if (targetRespawn < 0)
		{
			TargetManager::GetInstance()->AddTargets(sf::Vector2f(395, 180), 100);
			TargetManager::GetInstance()->AddTargets(sf::Vector2f(600, 180), 100);
			TargetManager::GetInstance()->AddTargets(sf::Vector2f(810, 180), 100);
			SoundManager::GetInstance()->PlayClick();
			targetRespawn = targetRespawnTime;
		}
	}

	if (tut_displayTimer > tut_displayTime)
	{
		tut_ShootInfoDraw = false;
		tut_ReloadInfoDraw = false;
		tut_QuickReloadDraw = false;
		tut_displayTimer = 0;
	}

	if (tut_ShootInfoDisplayed == false && gameTime > 2.0f)
	{
		tut_ShootInfoDraw = true;
		tut_ShootInfoDisplayed = true;
		infoSprite.setTexture(shootInfoTexture, true);
		SoundManager::GetInstance()->PlayInfoSoundEffect();
	}
	if (tut_ReloadInfoDisplayed == false && player->getClipCount() < player->getMaxClip()/2 && tut_ShootInfoDraw == false && tut_QuickReloadDraw == false)
	{
		tut_ReloadInfoDraw = true;
		tut_ReloadInfoDisplayed = true;
		infoSprite.setTexture(reloadInfoTexture, true);
		SoundManager::GetInstance()->PlayInfoSoundEffect();
	}
	if (tut_QuickReloadDisplayed == false && player->getClipCount() <= 3 && tut_ShootInfoDraw == false && tut_ReloadInfoDraw == false)
	{
		tut_QuickReloadDraw = true;
		tut_QuickReloadDisplayed = true;
		infoSprite.setTexture(quickReloadTexture, true);
		SoundManager::GetInstance()->PlayInfoSoundEffect();
	}

	if (tut_ShootInfoDraw == true || tut_ReloadInfoDraw == true || tut_QuickReloadDraw == true)
	{
		tut_displayTimer += frameTime;
	}
	//player->getClipCount();
	//player->getMaxClip();
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
	TargetManager::GetInstance()->AddTargets(sf::Vector2f(395, 180), 100);
	TargetManager::GetInstance()->AddTargets(sf::Vector2f(600, 180), 100);
	TargetManager::GetInstance()->AddTargets(sf::Vector2f(810, 180), 100);
}

void Level::DrawResult(sf::RenderWindow& window)
{
	ss.str(std::string());
	gameTime = roundf(gameTime * 100) / 100;
	ss << gameTime;
	string txt = "You shot 6 targets in: ";
	gameTimeText.setString(txt + ss.str() + " seconds");
	gameTimeText.setPosition(50, 600);

	window.draw(gameTimeText);
}