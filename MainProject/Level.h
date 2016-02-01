#include <iostream>
using namespace std;
#include "Player.h"
#include <sstream>


#ifndef LEVEL
#define LEVEL

class Level
{
public:
	Level();
	void Load();
	void SetUp();
	void DrawBG(sf::RenderWindow& window);
	void Update(Player *player, float);
	void Restart();
	void DrawResult(sf::RenderWindow& window);
	void Level::DrawOverlayUI(sf::RenderWindow& window);

private:
	sf::Texture rangeTexture;
	sf::Sprite rangeSprite;

	bool tut_ShootInfoDisplayed;
	bool tut_ReloadInfoDisplayed;
	bool tut_QuickReloadDisplayed;

	bool tut_ShootInfoDraw;
	bool tut_ReloadInfoDraw;
	bool tut_QuickReloadDraw;

	float tut_displayTime;
	float tut_displayTimer;

	float gameTime;
	float gameOverTime;

	float targetRespawn;
	float targetRespawnTime;

	sf::Font font;
	sf::Text gameTimeText;
	std::stringstream ss;

	//Sprite stuff

	sf::Texture shootInfoTexture;
	sf::Sprite shootInfoSprite;
	sf::Texture reloadInfoTexture;
	sf::Sprite reloadInfoSprite;
	sf::Texture quickReloadTexture;
	sf::Sprite quickReloadSprite;

	sf::Sprite infoSprite;

	//Sprite stuff
};

#endif 