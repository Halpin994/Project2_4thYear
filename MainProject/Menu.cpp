#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "Menu.h"
#include "GameStateManager.h"
//#include "CollisionManager.h"

#include "Button.h"
#include "SoundManager.h"
#include "LevelManager.h"

void (Menu::*playGameFunc)() = &Menu::PlayGame;
void (Menu::*quitFunc)() = &Menu::Quit;
void (Menu::*selectLevelFunc)() = &Menu::SelectLevel;
void (Menu::*selectLevelTypeFunc)() = &Menu::SelectLevelType;

Achievement* Menu::crapShot = new CrapShot();
Achievement* Menu::crackShot = new CrackShot();

Menu::Menu()
{
	MainFirstPos = sf::Vector2f(100, 200);
	MainSpacing = sf::Vector2f(0, 50);

	AddButton(MainFirstPos, sf::String("PLAY GAME"), 56, font, playGameFunc, mainButtons);
	AddButton(MainFirstPos + MainSpacing, sf::String("OPTIONS"), 56, font, quitFunc, mainButtons);
	AddButton(MainFirstPos + MainSpacing + MainSpacing, sf::String("QUIT"), 56, font, quitFunc, mainButtons);

	cleanMeUp = false;
	mainButtonsAlive = true;
	levelButtonsAlive = false;
	levelTypeButtonsAlive = false;
	Load();
	SetUp();

	achievements.push_back(crapShot);
	achievements.push_back(crackShot);
}

void Menu::Quit()
{
	GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::QUIT);
}

void Menu::SelectLevelType()
{
	if (firstButtonPressed == "Level 1")
	{
		if (secondButtonPressed == "Highscore")
		{
			LevelManager::GetInstance()->CreateLevel(sf::String("Level1-Highscore"), this);
			GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::GAME);
		}
		else if (secondButtonPressed == "Highspeed")
		{
			LevelManager::GetInstance()->CreateLevel(sf::String("Level1-Highspeed"), this);
			GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::GAME);
		}
		else if (secondButtonPressed == "Headshots")
		{
			LevelManager::GetInstance()->CreateLevel(sf::String("Level1-Headshots"), this);
			GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::GAME);
		}
	}
}

void Menu::SelectLevel()
{
	if (levelTypeButtonsAlive)
	{
		for (Button *b : levelTypeButtons)
		{
			delete b;
		}
		levelTypeButtons.clear();
		levelTypeButtonsAlive = false;
	}

	if (secondButtonPressed == "Level 2")
	{
		LevelTypeFirstPos = levelButtons.back()->GetPosition() + sf::Vector2f(levelButtons.front()->GetBounds().width + 50, levelButtons.front()->GetBounds().height / 4);
	}
	else
		LevelTypeFirstPos = levelButtons.front()->GetPosition() + sf::Vector2f(levelButtons.front()->GetBounds().width + 50, levelButtons.front()->GetBounds().height / 4);

	AddButton(LevelTypeFirstPos, sf::String("Highscore"), 24, font, selectLevelTypeFunc, levelTypeButtons);
	AddButton(LevelTypeFirstPos + sf::Vector2f(0, 28), sf::String("Highspeed"), 24, font, selectLevelTypeFunc, levelTypeButtons);
	AddButton(LevelTypeFirstPos + sf::Vector2f(0, 56), sf::String("Headshots"), 24, font, selectLevelTypeFunc, levelTypeButtons);

	levelTypeButtonsAlive = true;
}

void Menu::PlayGame()
{
	if (levelButtonsAlive)
	{
		for (Button *b : levelButtons)
		{
			delete b;
		}
		levelButtons.clear();
		levelButtonsAlive = false;
	}
	if (levelTypeButtonsAlive)
	{
		for (Button *b : levelTypeButtons)
		{
			delete b;
		}
		levelTypeButtons.clear();
		levelTypeButtonsAlive = false;
	}

	LevelFirstPos = mainButtons.front()->GetPosition() + sf::Vector2f(mainButtons.front()->GetBounds().width + 50, mainButtons.front()->GetBounds().height/4);

	AddButton(LevelFirstPos, sf::String("Level 1"), 30, font, selectLevelFunc, levelButtons);
	AddButton(LevelFirstPos + sf::Vector2f(0,35), sf::String("Level 2"), 30, font, selectLevelFunc, levelButtons);

	levelButtonsAlive = true;
}

void Menu::AddButton(sf::Vector2f pos, sf::String string, int size, sf::Font& font, void (Menu::*MenuMemFunc)(), list<Button*>& btns)
{
	Button *btn = new Button(pos, string, size, font, MenuMemFunc);
	btns.push_back(btn);
}

//! Load in assets
/*!
\Loads in the menu background image, menu selection images, and crosshair image then assigns it to their respective textures
\return none
\sa
*/
void Menu::Load()
{
	menuBG_tex.loadFromFile("Assets/Images/Menu/menuBG_img.png");
	crosshair_tex.loadFromFile("Assets/Images/crosshair.png");
	font.loadFromFile("Assets/imagine_font.ttf");
}

//! Setup the sprites
/*!
\Sets the crosshair sprites origin to the centre of the sprite. Sets the texture for each sprite and the position.
\return none
\sa
*/
void Menu::SetUp()
{
	//Set Textures
	crosshair_spr.setTexture(crosshair_tex);
	menuBG_spr.setTexture(menuBG_tex);

	//Set Origin
	crosshair_spr.setOrigin(75, 75);

	//Set Position
	menuBG_spr.setPosition(0, 0);
}

//! Draw the menu
/*!
\Draw the menu sprites relative to the window
\return none
\sa
*/
void Menu::Draw(sf::RenderWindow& window)
{
	window.draw(menuBG_spr);

	if (mainButtonsAlive)
	{
		for (Button *b : mainButtons)
		{
			b->Draw(window);
		}
	}
	if (levelButtonsAlive)
	{
		for (Button *b : levelButtons)
		{
			b->Draw(window);
		}
	}
	if (levelTypeButtonsAlive)
	{
		for (Button *b : levelTypeButtons)
		{
			b->Draw(window);
		}
	}
	int i = 0; // i is used to space out achievements 
	for (Achievement* achievement : achievements)
	{
		if (achievement->unlocked)
		{
			achievement->SetPosition(sf::Vector2f(50 + (100 * i), 600));
			achievement->Draw(window);
			i++;
		}
	}

	window.draw(crosshair_spr);
}

//! Update the menu cursor
/*!
\Updates the menu cursor relative to the position of the mouse on the window.
\return none
\sa
*/
void Menu::Update(sf::RenderWindow& window)
{
	crosshair_spr.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	if (cleanMeUp == true)
	{
		if (levelButtonsAlive)
		{
			for (Button *b : levelButtons)
			{
				delete b;
			}
			levelButtons.clear();
			levelButtonsAlive = false;
		}
		if (levelTypeButtonsAlive)
		{
			for (Button *b : levelTypeButtons)
			{
				delete b;
			}
			levelTypeButtons.clear();
			levelTypeButtonsAlive = false;
		}
		cleanMeUp = false;
	}

	if (mainButtonsAlive)
	{
		for (Button *b : mainButtons)
		{
			b->Update(crosshair_spr.getPosition(), this);
		}
	}
	if (levelButtonsAlive)
	{
		for (Button *b : levelButtons)
		{
			b->Update(crosshair_spr.getPosition(), this);
		}
	}
	if (levelTypeButtonsAlive)
	{
		for (Button *b : levelTypeButtons)
		{
			b->Update(crosshair_spr.getPosition(), this);
		}
	}
}

void Menu::SetFirstButtonPressed(sf::String button)
{
	firstButtonPressed = button;
}

void Menu::SetSecondButtonPressed(sf::String button)
{
	secondButtonPressed = button;
}
