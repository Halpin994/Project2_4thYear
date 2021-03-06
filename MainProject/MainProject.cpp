#include "stdafx.h"
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Menu.h"
#include "Level.h"
#include "Target.h"
#include "GameStateManager.h"
#include "BulletManager.h"
#include "TargetManager.h"
#include "SoundManager.h"

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
int main()
{
	//sf::View view(sf::FloatRect(0, 0, 1200, 700));
	sf::RenderWindow window(sf::VideoMode(1200, 700), "Main Project");
	//window.setView(view);
	sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);
	window.setMouseCursorVisible(false);
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);
	GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::MAIN_MENU);
	sf::Clock clock;
	Menu *menu = new Menu();
	Player *player = new Player();

	SoundManager::GetInstance(); //calling constructor for sm to load assets

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

			menu->Update(window);

			window.clear(); //clear the previous screen
			menu->Draw(window);
			menu->DrawCrosshair(window);
			window.display(); //display the updated screen

			break;
		case GameStateManager::GameStates::OPTIONS: //Options state

			menu->Update(window);
			menu->CheckMouseOptions(window);

			window.clear(); //clear the previous screen
			menu->Draw(window);
			menu->DrawOptions(window);
			menu->DrawCrosshair(window);
			window.display(); //display the updated screen


			break;
		case GameStateManager::GameStates::GAME: //Game state

			Level::GetInstance()->Update(player, time);
			player->Update(window, time);

			window.clear(); //clear the previous screen

			Level::GetInstance()->Draw(window);
			player->Draw(window);
			Level::GetInstance()->DrawOverlayUI(window);

			window.display(); //display the updated screen
			break;
		case GameStateManager::GameStates::GAMEOVER: //Gameover state
			window.clear(); //clear the previous screen
			Level::GetInstance()->DrawResult(window);
			window.display(); //display the updated screen
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				player->Restart();
				Level::GetInstance()->Restart();
				GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::GAME);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			{
				Level::GetInstance()->SetLevel(1);
				player->Restart();
				Level::GetInstance()->Restart();
				GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::GAME);
			}
			break;
		case GameStateManager::GameStates::QUIT: //Quit game state
			window.close();
			break;
		}

	}//end while

	return 0;
}

