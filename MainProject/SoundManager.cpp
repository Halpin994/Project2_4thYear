#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>

#include "SoundManager.h"

#include <deque>

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
	menuGunShot_buff.loadFromFile("Assets/Sounds/menuGunShot.wav");
	metalClang_buff.loadFromFile("Assets/Sounds/metalClang.wav");
	woodClang_buff.loadFromFile("Assets/Sounds/woodKlang.wav");
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
	menuGunShot_sfx.setBuffer(menuGunShot_buff);
	metalClang_sfx.setBuffer(metalClang_buff);
	woodClang_sfx.setBuffer(woodClang_buff);

	SetVolume();
}

void SoundManager::Update()
{
	for (int i = 0; i < soundInstances.size(); ++i)
	{
		if (soundInstances[i].getStatus() == sf::Sound::Stopped)
		{	
			soundInstances.erase(soundInstances.begin() + i);
			--i;
		}
	}
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
	soundInstances.push_back(sf::Sound(pistolGunShot_buff));
	soundInstances.back().play();
}

void SoundManager::PlayClick()
{
	soundInstances.push_back(sf::Sound(click_buff));
	soundInstances.back().play();
}

void SoundManager::PlayOutOfAmmo()
{
	soundInstances.push_back(sf::Sound(noAmmo_buff));
	soundInstances.back().play();
}

void SoundManager::PlayFallingShell()
{
	soundInstances.push_back(sf::Sound(fallingShell_buff));
	soundInstances.back().play();
}

void SoundManager::PlayPistolReload()
{
	soundInstances.push_back(sf::Sound(pistolReload_buff));
	soundInstances.back().play();
}

void SoundManager::PlayPistolQuickReload()
{
	soundInstances.push_back(sf::Sound(pistolQuickReload_buff));
	soundInstances.back().play();
}

void SoundManager::PlayInfoSoundEffect()
{
	soundInstances.push_back(sf::Sound(infoSoundEffect_buff));
	soundInstances.back().play();
}

void SoundManager::PlayMenuShotSoundEffect()
{
	soundInstances.push_back(sf::Sound(menuGunShot_buff));
	soundInstances.back().play();
}

void SoundManager::PlayMetalClangSoundEffect()
{
	soundInstances.push_back(sf::Sound(metalClang_buff));
	soundInstances.back().play();
}
void SoundManager::PlayWoodClangSoundEffect()
{
	soundInstances.push_back(sf::Sound(woodClang_buff));
	soundInstances.back().play();
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
	menuGunShot_sfx.setVolume(volume);
	metalClang_sfx.setVolume(volume);
	woodClang_sfx.setVolume(volume);
}


