#ifndef MENU
#define MENU

#include <iostream>
#include <sstream>
#include <list>
#include "Button.h"
using namespace std;


//typedef  void (Menu::*MenuMemFunc)();
//class Button;
class Menu
{
public:
	Menu();
	void Menu::Load();
	void Menu::SetUp();

	void Menu::Draw(sf::RenderWindow& window);
	//void Menu::DrawOptions(sf::RenderWindow& window);
	//void Menu::DrawCrosshair(sf::RenderWindow& window);

	void Menu::Update(sf::RenderWindow& window);

	//void Menu::CheckMouseMenu(sf::RenderWindow& window);
	//void Menu::CheckMouseOptions(sf::RenderWindow& window);
	//void Menu::CheckMouseLevelSelect(sf::RenderWindow& window);

	//void Menu::DrawLevelSelect(sf::RenderWindow& window);

	void Menu::Quit();
	void Menu::PlayGame();
	void Menu::SelectLevel();
	void Menu::SelectLevelType();
	void Menu::AddButton(sf::Vector2f pos, sf::String string, int size, sf::Font& font, void (Menu::*MenuMemFunc)(), list<Button*>& btns);
	void Menu::SetSecondButtonPressed(sf::String button);
	void Menu::SetFirstButtonPressed(sf::String button);
	//GameStateManager stateManager;

private:
	sf::Texture menuBG_tex;
	//sf::Texture volumeOption_tex;
	//sf::Texture playGame_tex;
	//sf::Texture playGameHighlight_tex;
	//sf::Texture options_tex;
	//sf::Texture optionsHighlight_tex;
	//sf::Texture quit_tex;
	//sf::Texture quitHighlight_tex;
	sf::Texture crosshair_tex;

	//sf::Texture volume_tex;
	//sf::Texture volumeUp_tex;
	//sf::Texture volumeUpHighlight_tex;
	//sf::Texture volumeDown_tex;
	//sf::Texture volumeDownHighlight_tex;
	
	//sf::Texture volumeOptionHighlight_tex;

	sf::Sprite menuBG_spr;
	//sf::Sprite playGame_spr;
	//sf::Sprite options_spr;
	//sf::Sprite quit_spr;
	sf::Sprite crosshair_spr;

	//sf::Sprite volume_spr;
	//sf::Sprite volumeUp_spr;
	//sf::Sprite volumeDown_spr;

	//bool highlighted;
	//bool optionsHighlighted;
	//bool level1Highlighted;
	//bool level2Highlighted;
	//bool levelModeHighlighted;
	//bool displayLevel1Modes;
	//bool displayLevel2Modes;

	//bool volumeClicked;

	//float volUpPos_x;
	//float volDownPos_x;

	sf::Font font;
	sf::Text volumeText;
	std::stringstream ss;

	sf::Vector2f MainFirstPos;
	sf::Vector2f LevelFirstPos;
	sf::Vector2f LevelTypeFirstPos;
	sf::Vector2f MainSpacing;

	sf::String secondButtonPressed;
	sf::String firstButtonPressed;

	//sf::Text Level_1_Text;
	//sf::Text Level_1_Headshots_Text;
	//sf::Text Level_1_Score_Text;
	//sf::Text Level_1_Speed_Text;

	//sf::Text Level_2_Text;
	//sf::Text Level_2_Headshots_Text;
	//sf::Text Level_2_Score_Text;
	//sf::Text Level_2_Speed_Text;

	//std::list<Button*> buttons;
	list<Button*> mainButtons;
	list<Button*> levelButtons;
	list<Button*> levelTypeButtons;

	bool mainButtonsAlive;
	bool levelButtonsAlive;
	bool levelTypeButtonsAlive;
};

#endif 