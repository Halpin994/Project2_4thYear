#ifndef LEVELMANAGER
#define LEVELMANAGER

using namespace std;
#include "Player.h"
#include "Level.h"
#include <list>
#include <sstream>
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
	void LevelManager::CreateLevel(string lvl);
	void LevelManager::Draw(sf::RenderWindow& window);
	void LevelManager::Update(Player* player, float time);
	Level* LevelManager::GetCurrentLevel();
private:
	static bool instanceFlag;
	static LevelManager* instance;

	LevelManager();

	Level *level;
	sf::Texture targetImage, bulletImage, layer0_Image, layer1_Image, layer2_Image, layer3_Image, layer4_Image;
};

#endif 
