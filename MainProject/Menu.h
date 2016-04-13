#include <iostream>
#include <sstream>
using namespace std;

#ifndef MENU
#define MENU

class Menu
{
public:
	Menu();
	void Menu::Load();
	void Menu::SetUp();

	void Menu::Draw(sf::RenderWindow& window);
	void Menu::DrawOptions(sf::RenderWindow& window);
	void Menu::DrawCrosshair(sf::RenderWindow& window);

	void Menu::Update(sf::RenderWindow& window);

	void Menu::CheckMouseMenu(sf::RenderWindow& window);
	void Menu::CheckMouseOptions(sf::RenderWindow& window);
	void Menu::CheckMouseLevelSelect(sf::RenderWindow& window);

	void Menu::DrawLevelSelect(sf::RenderWindow& window);
	//GameStateManager stateManager;

private:
	sf::Texture menuBG_tex;
	sf::Texture volumeOption_tex;
	sf::Texture playGame_tex;
	sf::Texture playGameHighlight_tex;
	sf::Texture options_tex;
	sf::Texture optionsHighlight_tex;
	sf::Texture quit_tex;
	sf::Texture quitHighlight_tex;
	sf::Texture crosshair_tex;

	sf::Texture volume_tex;
	sf::Texture volumeUp_tex;
	sf::Texture volumeUpHighlight_tex;
	sf::Texture volumeDown_tex;
	sf::Texture volumeDownHighlight_tex;
	
	//sf::Texture volumeOptionHighlight_tex;

	sf::Sprite menuBG_spr;
	sf::Sprite playGame_spr;
	sf::Sprite options_spr;
	sf::Sprite quit_spr;
	sf::Sprite crosshair_spr;

	sf::Sprite volume_spr;
	sf::Sprite volumeUp_spr;
	sf::Sprite volumeDown_spr;

	bool highlighted;
	bool optionsHighlighted;
	bool levelHighlighted;

	bool volumeClicked;

	float volUpPos_x;
	float volDownPos_x;

	sf::Font font;
	sf::Text volumeText;
	std::stringstream ss;

	sf::Text Level_1_Text;
	sf::Text Level_1_Headshots_Text;
	sf::Text Level_1_Score_Text;
	sf::Text Level_1_Speed_Text;

};
#endif 