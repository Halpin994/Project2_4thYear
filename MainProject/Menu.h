#include <iostream>
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
	void Menu::Update(sf::RenderWindow& window);
	void Menu::Select(sf::RenderWindow& window);
	void Menu::Highlight(sf::RenderWindow& window);

	//GameStateManager stateManager;

private:
	sf::Texture menuBG_tex;
	sf::Texture playGame_tex;
	sf::Texture playGameHighlight_tex;
	sf::Texture options_tex;
	sf::Texture optionsHighlight_tex;
	sf::Texture quit_tex;
	sf::Texture quitHighlight_tex;
	sf::Texture crosshair_tex;

	sf::Sprite menuBG_spr;
	sf::Sprite playGame_spr;
	sf::Sprite options_spr;
	sf::Sprite quit_spr;
	sf::Sprite crosshair_spr;

	bool highlighted;
};
#endif 