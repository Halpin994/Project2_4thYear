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
	void Draw(sf::RenderWindow& window);
	void Update(Player *player, float);
	void Restart();
	void DrawResult(sf::RenderWindow& window);
	void Level::DrawOverlayUI(sf::RenderWindow& window);

	void Level::UpdateTut(Player *player, float frameTime);
	void SetLevel1();

private:
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

	enum class LevelStates { TUTORIAL, LEVEL1 };

	LevelStates levelState;

	//Sprite stuff
};

#endif 