#include "stdafx.h"
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Menu.h"
#include "Level.h"
#include "Target.h"
#include "GameStateManager.h"
#include "BulletManager.h"

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 700), "Main Project");
	sf::Mouse::setPosition(sf::Vector2i(600, 350), window);
	window.setMouseCursorVisible(false);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::MAIN_MENU);

	sf::Clock clock;

	Player player;
	player.Init(window);
	Menu menu;
	Level level;
	Target target;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		//cout << time << endl;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();

		switch (GameStateManager::GetInstance()->GetGameState()) 
		{
		case GameStateManager::GameStates::MAIN_MENU:
			menu.Update(window);

			window.clear();
			menu.Draw(window);
			window.display();

			break;
		case GameStateManager::GameStates::GAME:
			player.Update(window, time);

			window.clear();
			level.Draw(window);
			target.Draw(window);
			BulletManager::GetInstance()->Draw(window);
			player.Draw(window);
			window.display();
			break;
		case GameStateManager::GameStates::OPTIONS:

			break;
		case GameStateManager::GameStates::QUIT:
			window.close();
			break;
		}

		
	}

	return 0;
}

