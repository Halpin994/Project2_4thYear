#include <iostream>
using namespace std;
#include "Player.h"
#include "Target.h"
#include <sstream>


#ifndef LEVEL
#define LEVEL

class Level
{
public:

	//static Level* GetInstance();

	//~Level()
	//{
	//	instanceFlag = false;
	//}
	//enum LevelStates { LEVEL1, LEVEL2 };
	Level(string lvl);
	void Load();
	void SetUp();
	void Draw(sf::RenderWindow& window, int layer);
	void Update(Player *player, double frameTime);
	void Restart();
	void DrawResult(sf::RenderWindow& window);
	void Level::DrawOverlayUI(sf::RenderWindow& window);

	void Level::UpdateTut(Player *player, double frameTime);
	void SetLevel(int lvl);
	//LevelStates Level::GetLevelState();

	void AddTarget(sf::Vector2f pos, sf::Texture* targetImage, sf::Texture* bulletImage, float health, int layer);
	void AddLevelSprite(sf::Texture* levelImage, int layer, sf::Vector2f position);

	list<Target*> Level::GetListOfTargets();

	//void Level::SetEndState(string lvl);
	bool Level::CheckEndState();

	string Level::GetLevelType();

private:
	//{
	//	levelState = LevelStates::LEVEL1;

	//	tut_ShootInfoDisplayed = false;
	//	tut_ReloadInfoDisplayed = false;
	//	tut_QuickReloadDisplayed = false;

	//	tut_ShootInfoDraw = false;
	//	tut_ReloadInfoDraw = false;
	//	tut_QuickReloadDraw = false;

	//	gameTime = 0;
	//	gameOverTime = 0;

	//	targetRespawnTime = 0.4;
	//	targetRespawn = targetRespawnTime;
	//}

	//static bool instanceFlag;
	//static Level* instance;


	sf::Texture rangeBgTexture;
	sf::Texture level1BgTexture;
	sf::Sprite bgSprite;

	sf::Texture texture_level1Layer1;
	sf::Texture texture_level1Layer2;
	sf::Texture texture_level1Layer3;
	sf::Texture texture_level1Layer4;

	sf::Sprite spr_level1Layer1;
	sf::Sprite spr_level1Layer2;
	sf::Sprite spr_level1Layer3;
	sf::Sprite spr_level1Layer4;

	bool tut_ShootInfoDisplayed;
	bool tut_ReloadInfoDisplayed;
	bool tut_QuickReloadDisplayed;

	bool tut_ShootInfoDraw;
	bool tut_ReloadInfoDraw;
	bool tut_QuickReloadDraw;

	bool levelEnd;

	float tut_displayTime;
	float tut_displayTimer;

	double gameTime;
	float gameOverTime;
	float frameRate;
	float frameRateSum;
	int frameNum;

	float targetRespawn;
	float targetRespawnTime;

	sf::Font font;
	sf::Text gameTimeText;
	sf::Text frameRateText;
	std::stringstream ss;

	//Sprite stuff

	sf::Texture shootInfoTexture;
	sf::Sprite shootInfoSprite;
	sf::Texture reloadInfoTexture;
	sf::Sprite reloadInfoSprite;
	sf::Texture quickReloadTexture;
	sf::Sprite quickReloadSprite;

	sf::Sprite infoSprite;

	list<Target*> targets;
	list<std::pair<sf::Sprite, int>> levelSprites;

	sf::String currentLevel;

	//std::multimap<sf::Sprite, int> myMap;
	//myMap.insert(std::pair<char, char>('A', 'B'));
	//myMap.insert(std::pair<char, char>('A', 'C'));

	//LevelStates levelState;

	//Sprite stuff
};

#endif 