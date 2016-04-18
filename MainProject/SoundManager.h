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
		volume = 10;

		Load();
		SetUp();
	}
	static bool instanceFlag;
	static SoundManager* instance;

	std::deque<sf::Sound> soundInstances;

	sf::SoundBuffer pistolGunShot_buff;
	sf::SoundBuffer click_buff;
	sf::SoundBuffer noAmmo_buff;
	sf::SoundBuffer fallingShell_buff;
	sf::SoundBuffer pistolReload_buff;
	sf::SoundBuffer pistolQuickReload_buff;
	sf::SoundBuffer infoSoundEffect_buff;
	sf::SoundBuffer menuGunShot_buff;
	sf::SoundBuffer metalClang_buff;
	sf::SoundBuffer woodClang_buff;

	int volume;
};

#endif 