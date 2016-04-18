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

	Level(string lvl);
	void Load();
	void SetUp();
	void Draw(sf::RenderWindow& window);
	void DrawLayer(sf::RenderWindow& window, int layer);
	void Update(double frameTime, sf::RenderWindow& window);
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

	sf::Texture statsTexture;
	sf::Sprite statsSprite;

	sf::Texture shootInfoTexture;
	sf::Sprite shootInfoSprite;
	sf::Texture reloadInfoTexture;
	sf::Sprite reloadInfoSprite;
	sf::Texture quickReloadTexture;
	sf::Sprite quickReloadSprite;

	sf::Sprite infoSprite;

	Player* player;

	list<Target*> targets;
	list<std::pair<sf::Sprite, int>> levelSprites;

	sf::String currentLevel;
};

#endif 