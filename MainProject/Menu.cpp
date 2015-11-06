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

void Menu::Load()
{
	menuBG_img.loadFromFile("menuBG_img.png");
	playGame_img.loadFromFile("playGame_img.png");
	options_img.loadFromFile("options_img.png");
	quit_img.loadFromFile("quit_img.png");
	crosshair_img.loadFromFile("crosshair.png");
}

void Menu::SetUp()
{
	crosshair_spr.setOrigin(75, 75);
	crosshair_spr.setTexture(crosshair_img);

	menuBG_spr.setTexture(menuBG_img);
	playGame_spr.setTexture(playGame_img);
	options_spr.setTexture(options_img);
	quit_spr.setTexture(quit_img);

	menuBG_spr.setPosition(0, 0);
	playGame_spr.setPosition(100, 150);
	options_spr.setPosition(100, 300);
	quit_spr.setPosition(100, 450);
}

void Menu::Draw(sf::RenderWindow& window)
{
	window.draw(menuBG_spr);
	window.draw(playGame_spr);
	window.draw(options_spr);
	window.draw(quit_spr);
	window.draw(crosshair_spr);
}

void Menu::Update(sf::RenderWindow& window)
{
	crosshair_spr.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	Menu::Select(window);
}

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