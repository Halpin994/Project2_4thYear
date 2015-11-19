#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "Menu.h"
#include "GameStateManager.h"

Menu::Menu()
{
	Load();
	SetUp();
}

//! Load in assets
/*!
\Loads in the menu background image, menu selection images, and crosshair image then assigns it to their respective textures
\return none
\sa
*/
void Menu::Load()
{
	menuBG_tex.loadFromFile("menuBG_img.png");
	playGame_tex.loadFromFile("playGame_img.png");
	options_tex.loadFromFile("options_img.png");
	quit_tex.loadFromFile("quit_img.png");
	crosshair_tex.loadFromFile("crosshair.png");
}

//! Setup the sprites
/*!
\Sets the crosshair sprites origin to the centre of the sprite. Sets the texture for each sprite and the position.
\return none
\sa
*/
void Menu::SetUp()
{
	crosshair_spr.setOrigin(75, 75);
	crosshair_spr.setTexture(crosshair_tex);

	menuBG_spr.setTexture(menuBG_tex);
	playGame_spr.setTexture(playGame_tex);
	options_spr.setTexture(options_tex);
	quit_spr.setTexture(quit_tex);

	menuBG_spr.setPosition(0, 0);
	playGame_spr.setPosition(100, 150);
	options_spr.setPosition(100, 300);
	quit_spr.setPosition(100, 450);
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
	window.draw(playGame_spr);
	window.draw(options_spr);
	window.draw(quit_spr);
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
	Menu::Select(window);
}

//! Select Option
/*!
\Determines which option is being selected in the menu using box collision. Sets the game state depending on which collision is detected
\return none
\sa
*/
void Menu::Select(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (sf::Mouse::getPosition(window).x > playGame_spr.getPosition().x && sf::Mouse::getPosition(window).x < playGame_spr.getPosition().x + playGame_spr.getGlobalBounds().width
			&& sf::Mouse::getPosition(window).y > playGame_spr.getPosition().y && sf::Mouse::getPosition(window).y < playGame_spr.getPosition().y + playGame_spr.getGlobalBounds().height)
		{
			sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);
			GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::GAME);
		}
		else if (sf::Mouse::getPosition(window).x > quit_spr.getPosition().x && sf::Mouse::getPosition(window).x < quit_spr.getPosition().x + quit_spr.getGlobalBounds().width
			&& sf::Mouse::getPosition(window).y > quit_spr.getPosition().y && sf::Mouse::getPosition(window).y < quit_spr.getPosition().y + quit_spr.getGlobalBounds().height)
		{
			GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::QUIT);
		}
	}
}