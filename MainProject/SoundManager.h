#include <iostream>
#include <list>

using namespace std;

#ifndef SOUNDMANAGER
#define SOUNDMANAGER

#include "SFML\Audio.hpp"

class SoundManager
{
public:
	~SoundManager()
	{
		delete instance;
		instanceFlag = false;
	}
	static SoundManager* GetInstance();

	void SoundManager::Load();
	void SoundManager::SetUp();

	void SoundManager::PlayPistolGunShot();
	void SoundManager::PlayClick();
	void SoundManager::PlayOutOfAmmo();

private:
	SoundManager()
	{
		Load();
		SetUp();
		
	}
	static bool instanceFlag;
	static SoundManager* instance;

	sf::SoundBuffer pistolGunShot_buff;
	sf::Sound pistolGunShot_sfx;
	sf::SoundBuffer click_buff;
	sf::Sound click_sfx;
	sf::SoundBuffer noAmmo_buff;
	sf::Sound noAmmo_sfx;
};

#endif 