#ifndef LEVELMANAGER
#define LEVELMANAGER

using namespace std;
#include "Player.h"
#include "Level.h"
#include <list>
#include <sstream>
#include "Menu.h"
class LevelManager
{
public:
	static LevelManager* GetInstance();

	~LevelManager()
	{
		instanceFlag = false;
		delete level;
	}

	void LevelManager::DrawOverlayUI(sf::RenderWindow& window);
	void LevelManager::CreateLevel(string lvl, Menu* menu);
	void LevelManager::Draw(sf::RenderWindow& window);
	void LevelManager::Update(float time, sf::RenderWindow& window);
	Level* LevelManager::GetCurrentLevel();
	bool LevelManager::CheckEndState();
	void LevelManager::AddShotFired(sf::String location);
	float LevelManager::GetAccuracy();
	sf::String LevelManager::GetCurrentLevelType();
	sf::String LevelManager::GetCurrentType();


private:
	static bool instanceFlag;
	static LevelManager* instance;

	LevelManager();

	sf::String currentLevelandType;
	sf::String currentLevelType;

	bool levelEnd;

	float gameOverTime;
	float targRespawnTime;

	float Accuracy;

	int currentLevel;

	int numOfTotalShots;
	int topTargYellowHits;
	int topTargRedHits;
	int topTargBlueHits;
	int topTargWhiteHits;
	int bottomTargYellowHits;
	int bottomTargRedHits;
	int bottomTargBlueHits;
	int bottomTargWhiteHits;

	Level *level;
	sf::Texture targetImage, bulletImage, layer0_Image, layer1_Image, layer2_Image, layer3_Image, layer4_Image;
};

#endif 
