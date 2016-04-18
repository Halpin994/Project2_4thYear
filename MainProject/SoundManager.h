#include <iostream>
#include <list>
#include <deque>

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

	void SoundManager::Update();

	void SoundManager::PlayPistolGunShot();
	void SoundManager::PlayClick();
	void SoundManager::PlayOutOfAmmo();
	void SoundManager::PlayFallingShell();
	void SoundManager::PlayPistolReload();
	void SoundManager::PlayPistolQuickReload();
	void SoundManager::PlayInfoSoundEffect();
	void SoundManager::PlayMenuShotSoundEffect();
	void SoundManager::PlayMetalClangSoundEffect();
	void SoundManager::PlayWoodClangSoundEffect();
	void SoundManager::IncreaseVolume();
	void SoundManager::DecreaseVolume();
	int SoundManager::GetVolume();
	void SoundManager::SetVolume();

private:
	SoundManager()
	{
		volume = 50;

		Load();
		SetUp();
	}
	static bool instanceFlag;
	static SoundManager* instance;

	std::deque<sf::Sound> soundInstances;

	sf::SoundBuffer pistolGunShot_buff;
	sf::Sound pistolGunShot_sfx;
	sf::SoundBuffer click_buff;
	sf::Sound click_sfx;
	sf::SoundBuffer noAmmo_buff;
	sf::Sound noAmmo_sfx;
	sf::SoundBuffer fallingShell_buff;
	sf::Sound fallingShell_sfx;
	sf::SoundBuffer pistolReload_buff;
	sf::Sound pistolReload_sfx;
	sf::SoundBuffer pistolQuickReload_buff;
	sf::Sound pistolQuickReload_sfx;
	sf::SoundBuffer infoSoundEffect_buff;
	sf::Sound infoSoundEffect_sfx;

	sf::SoundBuffer menuGunShot_buff;
	sf::Sound menuGunShot_sfx;
	sf::SoundBuffer metalClang_buff;
	sf::Sound metalClang_sfx;
	sf::SoundBuffer woodClang_buff;
	sf::Sound woodClang_sfx;

	int volume;
};

#endif 