#include "stdafx.h"
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Menu.h"
#include "Level.h"
#include "Target.h"
#include "GameStateManager.h"
#include "BulletManager.h"
#include "TargetManager.h"

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
	Menu menu;
	Level level;
	Player player;

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) //closes the screen when the escape key is pressed
			window.close();

		switch (GameStateManager::GetInstance()->GetGameState()) 
		{
		case GameStateManager::GameStates::MAIN_MENU: //Menu state
			menu.Update(window);

			window.clear(); //clear the previous screen
			menu.Draw(window);
			window.display(); //display the updated screen

			break;
		case GameStateManager::GameStates::GAME: //Game state
			//player.Init(window);
			player.Update(window, time);
			window.clear(); //clear the previous screen
			level.Draw(window);
			TargetManager::GetInstance()->Draw(window);
			BulletManager::GetInstance()->Draw(window);
			player.Draw(window);
			window.display(); //display the updated screen
			break;
		case GameStateManager::GameStates::OPTIONS: //Options state

			break;
		case GameStateManager::GameStates::QUIT: //Quit game state
			window.close();
			break;
		}

	}//end while

	return 0;
}

