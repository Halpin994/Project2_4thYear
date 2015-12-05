#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>

#include "SoundManager.h"

bool SoundManager::instanceFlag = false;
SoundManager* SoundManager::instance = NULL;

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
SoundManager* SoundManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new SoundManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void SoundManager::Load()
{
	pistolGunShot_buff.loadFromFile("Assets/Sounds/gunShot.wav");
	click_buff.loadFromFile("Assets/Sounds/click.wav");
}
void SoundManager::SetUp()
{
	pistolGunShot_sfx.setBuffer(pistolGunShot_buff);
	click_sfx.setBuffer(click_buff);
}

void SoundManager::PlayPistolGunShot()
{
	pistolGunShot_sfx.play();
}

void SoundManager::PlayClick()
{
	click_sfx.play();
}

