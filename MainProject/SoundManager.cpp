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
	noAmmo_buff.loadFromFile("Assets/Sounds/noAmmo.wav");
	fallingShell_buff.loadFromFile("Assets/Sounds/fallingShell.wav");
	pistolReload_buff.loadFromFile("Assets/Sounds/pistolReload.wav");
	pistolQuickReload_buff.loadFromFile("Assets/Sounds/pistolQuickReload.wav");
	infoSoundEffect_buff.loadFromFile("Assets/Sounds/tut_infos.wav");
}
void SoundManager::SetUp()
{
	pistolGunShot_sfx.setBuffer(pistolGunShot_buff);
	click_sfx.setBuffer(click_buff);
	noAmmo_sfx.setBuffer(noAmmo_buff);
	fallingShell_sfx.setBuffer(fallingShell_buff);
	pistolReload_sfx.setBuffer(pistolReload_buff);
	pistolQuickReload_sfx.setBuffer(pistolQuickReload_buff);
	infoSoundEffect_sfx.setBuffer(infoSoundEffect_buff);
}

void SoundManager::IncreaseVolume()
{
	if (volume <= 45)
	{
		volume += 5;
	}
	//cout << volume << endl;
	SetVolume();
}
void SoundManager::DecreaseVolume()
{
	if (volume >= 5)
	{
		volume -= 5;
	}
	//cout << volume << endl;
	SetVolume();
}

void SoundManager::PlayPistolGunShot()
{

	pistolGunShot_sfx.play();
}

void SoundManager::PlayClick()
{
	
	click_sfx.play();
}

void SoundManager::PlayOutOfAmmo()
{
	
	noAmmo_sfx.play();
}

void SoundManager::PlayFallingShell()
{
	
	fallingShell_sfx.play();
}

void SoundManager::PlayPistolReload()
{
	
	pistolReload_sfx.play();
}

void SoundManager::PlayPistolQuickReload()
{
	
	pistolQuickReload_sfx.play();
}

void SoundManager::PlayInfoSoundEffect()
{
	
	infoSoundEffect_sfx.play();
}

int SoundManager::GetVolume()
{
	return volume;
}

void SoundManager::SetVolume()
{
	pistolGunShot_sfx.setVolume(volume);
	click_sfx.setVolume(volume);
	noAmmo_sfx.setVolume(volume);
	fallingShell_sfx.setVolume(volume);
	pistolReload_sfx.setVolume(volume);
	pistolQuickReload_sfx.setVolume(volume);
	infoSoundEffect_sfx.setVolume(volume);
}


