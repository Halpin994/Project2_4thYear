#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "Menu.h"
#include "GameStateManager.h"
#include "CollisionManager.h"

#include "SoundManager.h"
#include "LevelManager.h"

Menu::Menu()
{
	highlighted = false;
	optionsHighlighted = false;
	volumeClicked = false;

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
	menuBG_tex.loadFromFile("Assets/Images/Menu/menuBG_img.png");
	playGame_tex.loadFromFile("Assets/Images/Menu/playGame_img.png");
	playGameHighlight_tex.loadFromFile("Assets/Images/Menu/playGameHighlight_img.png");
	options_tex.loadFromFile("Assets/Images/Menu/options_img.png");
	optionsHighlight_tex.loadFromFile("Assets/Images/Menu/optionsHighlight_img.png");
	quit_tex.loadFromFile("Assets/Images/Menu/quit_img.png");
	quitHighlight_tex.loadFromFile("Assets/Images/Menu/quitHighlight_img.png");
	crosshair_tex.loadFromFile("Assets/Images/crosshair.png");

	volume_tex.loadFromFile("Assets/Images/Menu/Options/volume_img.png");
	volumeDown_tex.loadFromFile("Assets/Images/Menu/Options/volumeDown_img.png");
	volumeDownHighlight_tex.loadFromFile("Assets/Images/Menu/Options/volumeDownHighlight_img.png");
	volumeUp_tex.loadFromFile("Assets/Images/Menu/Options/volumeUp_img.png");
	volumeUpHighlight_tex.loadFromFile("Assets/Images/Menu/Options/volumeUpHighlight_img.png");

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

	volume_spr.setTexture(volume_tex);
	volumeUp_spr.setTexture(volumeUp_tex);
	volumeDown_spr.setTexture(volumeDown_tex);

	menuBG_spr.setTexture(menuBG_tex);
	playGame_spr.setTexture(playGame_tex);
	options_spr.setTexture(options_tex);
	quit_spr.setTexture(quit_tex);
	//Set Textures

	//Set Origin
	crosshair_spr.setOrigin(75, 75);

	playGame_spr.setOrigin(0, playGame_spr.getGlobalBounds().height / 2);
	options_spr.setOrigin(0, options_spr.getGlobalBounds().height / 2);
	quit_spr.setOrigin(0, quit_spr.getGlobalBounds().height / 2);

	volume_spr.setOrigin(0, volume_spr.getGlobalBounds().height / 2);
	volumeUp_spr.setOrigin(0, volumeUp_spr.getGlobalBounds().height / 2);
	volumeDown_spr.setOrigin(0, volumeDown_spr.getGlobalBounds().height / 2);
	//Set Origin

	//Set Position
	menuBG_spr.setPosition(0, 0);
	playGame_spr.setPosition(100, 250);
	options_spr.setPosition(playGame_spr.getPosition().x, playGame_spr.getPosition().y + 50);
	quit_spr.setPosition(playGame_spr.getPosition().x, options_spr.getPosition().y + 50);

	volume_spr.setPosition(playGame_spr.getPosition().x + playGame_spr.getGlobalBounds().width + 50, options_spr.getPosition().y);
	volumeDown_spr.setPosition(volume_spr.getPosition().x + volume_spr.getGlobalBounds().width + 20, volume_spr.getPosition().y);
	volumeUp_spr.setPosition(volumeDown_spr.getPosition().x + volumeDown_spr.getGlobalBounds().width + 20, volumeDown_spr.getPosition().y);

	volUpPos_x = volumeUp_spr.getPosition().x;
	volDownPos_x = volumeDown_spr.getPosition().x;
	//Set Position

	volumeText.setFont(font);
	volumeText.setCharacterSize(35);
	volumeText.setPosition(volDownPos_x + 70, volumeUp_spr.getPosition().y - volumeUp_spr.getGlobalBounds().height);
	volumeText.setColor(sf::Color::Green);

	Level_1_Text.setFont(font);
	Level_1_Text.setCharacterSize(22);
	Level_1_Text.setColor(sf::Color::White);
	Level_1_Text.setString("Level 1");
	Level_1_Text.setPosition(sf::Vector2f(playGame_spr.getPosition().x + playGame_spr.getGlobalBounds().width + 50, playGame_spr.getPosition().y - playGame_spr.getGlobalBounds().height / 1.5));

	Level_1_Score_Text.setFont(font);
	Level_1_Score_Text.setCharacterSize(22);
	Level_1_Score_Text.setColor(sf::Color::White);
	Level_1_Score_Text.setString("HighScore");
	Level_1_Score_Text.setPosition(sf::Vector2f(sf::Vector2f(Level_1_Text.getPosition().x + Level_1_Text.getGlobalBounds().width + 50, Level_1_Text.getPosition().y)));

	Level_1_Speed_Text.setFont(font);
	Level_1_Speed_Text.setCharacterSize(22);
	Level_1_Speed_Text.setColor(sf::Color::White);
	Level_1_Speed_Text.setString("HighSpeed");
	Level_1_Speed_Text.setPosition(sf::Vector2f(Level_1_Score_Text.getPosition().x, Level_1_Score_Text.getPosition().y + 30));

	Level_1_Headshots_Text.setFont(font);
	Level_1_Headshots_Text.setCharacterSize(22);
	Level_1_Headshots_Text.setColor(sf::Color::White);
	Level_1_Headshots_Text.setString("Headshots");
	Level_1_Headshots_Text.setPosition(sf::Vector2f(Level_1_Speed_Text.getPosition().x, Level_1_Speed_Text.getPosition().y + 30));

	Level_2_Text.setFont(font);
	Level_2_Text.setCharacterSize(22);
	Level_2_Text.setColor(sf::Color::White);
	Level_2_Text.setString("Level 2");
	Level_2_Text.setPosition(sf::Vector2f(Level_1_Text.getPosition().x, Level_1_Text.getPosition().y + 30));

	Level_2_Score_Text.setFont(font);
	Level_2_Score_Text.setCharacterSize(22);
	Level_2_Score_Text.setColor(sf::Color::White);
	Level_2_Score_Text.setString("HighScore");
	Level_2_Score_Text.setPosition(sf::Vector2f(sf::Vector2f(Level_1_Text.getPosition().x + Level_1_Text.getGlobalBounds().width + 50, Level_2_Text.getPosition().y)));

	Level_2_Speed_Text.setFont(font);
	Level_2_Speed_Text.setCharacterSize(22);
	Level_2_Speed_Text.setColor(sf::Color::White);
	Level_2_Speed_Text.setString("HighSpeed");
	Level_2_Speed_Text.setPosition(sf::Vector2f(Level_2_Score_Text.getPosition().x, Level_2_Score_Text.getPosition().y + 30));

	Level_2_Headshots_Text.setFont(font);
	Level_2_Headshots_Text.setCharacterSize(22);
	Level_2_Headshots_Text.setColor(sf::Color::White);
	Level_2_Headshots_Text.setString("Headshots");
	Level_2_Headshots_Text.setPosition(sf::Vector2f(Level_2_Speed_Text.getPosition().x, Level_2_Speed_Text.getPosition().y + 30));
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
}

void Menu::DrawOptions(sf::RenderWindow& window)
{
	window.draw(volume_spr);
	window.draw(volumeUp_spr);
	window.draw(volumeDown_spr);

	ss.str(std::string());
	ss << SoundManager::GetInstance()->GetVolume() * 2;
	volumeText.setString(ss.str());
	if (SoundManager::GetInstance()->GetVolume() > 25)
	{
		volumeText.setColor(sf::Color::Red);
	}
	else
		volumeText.setColor(sf::Color::Green);
	window.draw(volumeText);
}

void Menu::DrawLevelSelect(sf::RenderWindow& window)
{
	window.draw(Level_1_Text);
	window.draw(Level_2_Text);
	if (displayLevel1Modes)
	{
		window.draw(Level_1_Headshots_Text);
		window.draw(Level_1_Score_Text);
		window.draw(Level_1_Speed_Text);
	}
	if (displayLevel2Modes)
	{
		window.draw(Level_2_Headshots_Text);
		window.draw(Level_2_Score_Text);
		window.draw(Level_2_Speed_Text);
	}
}


void Menu::DrawCrosshair(sf::RenderWindow& window)
{
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
	CheckMouseMenu(window);
}

//! Select Option
/*!
\Determines which option is being selected in the menu using box collision. Sets the game state depending on which collision is detected
\return none
\sa
*/
//void Menu::Select(sf::RenderWindow& window)
//{
//	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//	{
//		if (CollisionManager::GetInstance()->CheckMenuElementCollision(sf::Mouse::getPosition(window), playGame_spr))
//		{
//			sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);
//			GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::GAME);
//		}
//		else if (CollisionManager::GetInstance()->CheckMenuElementCollision(sf::Mouse::getPosition(window), options_spr))
//		{
//			GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::OPTIONS);
//		}
//		else if (CollisionManager::GetInstance()->CheckMenuElementCollision(sf::Mouse::getPosition(window), quit_spr))
//		{
//			GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::QUIT);
//		}
//	}
//}

void Menu::CheckMouseMenu(sf::RenderWindow& window)
{
	if (playGame_spr.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))//(CollisionManager::GetInstance()->CheckMenuElementCollision(sf::Mouse::getPosition(window), playGame_spr.getPosition(), playGame_spr.getGlobalBounds()))
	{
		if (highlighted == false){
			GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::MAIN_MENU);
			SoundManager::GetInstance()->PlayClick();
			playGame_spr.setTexture(playGameHighlight_tex);
			highlighted = true;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);
			GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::LEVEL_SELECT);
			//LevelManager::GetInstance()->CreateLevel("Level1");


		}
	}
	else if (options_spr.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
	{
		if (highlighted == false){
			GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::MAIN_MENU);
			SoundManager::GetInstance()->PlayClick();
			options_spr.setTexture(optionsHighlight_tex);
			highlighted = true;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::OPTIONS);
		}
	}
	else if (quit_spr.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
	{
		if (highlighted == false){
			GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::MAIN_MENU);
			SoundManager::GetInstance()->PlayClick();
			quit_spr.setTexture(quitHighlight_tex);
			highlighted = true;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::QUIT);
		}
	}
	else
	{
		highlighted = false;
		playGame_spr.setTexture(playGame_tex);
		options_spr.setTexture(options_tex);
		quit_spr.setTexture(quit_tex);
	}
}

void Menu::CheckMouseOptions(sf::RenderWindow& window)
{
	if (volumeUp_spr.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
	{
		if (optionsHighlighted == false){
			SoundManager::GetInstance()->PlayClick();
			volumeUp_spr.setTexture(volumeUpHighlight_tex);
			optionsHighlighted = true;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && volumeClicked == false)
		{
			volumeClicked = true;
			volumeUp_spr.setPosition(volUpPos_x + 2, volumeUp_spr.getPosition().y);
			SoundManager::GetInstance()->IncreaseVolume();
			SoundManager::GetInstance()->PlayPistolGunShot();
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			volumeClicked = false;
			volumeUp_spr.setPosition(volUpPos_x, volumeUp_spr.getPosition().y);
		}
	}
	else if (volumeDown_spr.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
	{
		if (optionsHighlighted == false){
			SoundManager::GetInstance()->PlayClick();
			volumeDown_spr.setTexture(volumeDownHighlight_tex);
			optionsHighlighted = true;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && volumeClicked == false)
		{
			volumeClicked = true;
			volumeDown_spr.setPosition(volumeDown_spr.getPosition().x - 2, volumeDown_spr.getPosition().y);
			SoundManager::GetInstance()->DecreaseVolume();
			SoundManager::GetInstance()->PlayPistolGunShot();
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			volumeClicked = false;
			volumeDown_spr.setPosition(volDownPos_x, volumeDown_spr.getPosition().y);
		}
	}
	else
	{
		optionsHighlighted = false;
		volumeUp_spr.setTexture(volumeUp_tex);
		volumeDown_spr.setTexture(volumeDown_tex);
		volumeUp_spr.setPosition(volUpPos_x, volumeUp_spr.getPosition().y);
		volumeDown_spr.setPosition(volDownPos_x, volumeDown_spr.getPosition().y);
	}
}

void Menu::CheckMouseLevelSelect(sf::RenderWindow& window)
{
	if (Level_1_Text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
	{
		if (levelHighlighted == false)
		{
			
			Level_1_Text.setColor(sf::Color::Yellow);
			SoundManager::GetInstance()->PlayClick();
			levelHighlighted = true;

			
			displayLevel2Modes = false;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Level_1_Text.setString("Level  1 -> ");
			displayLevel1Modes = true;
			//LevelManager::GetInstance()->CreateLevel("Level1");
			//GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::GAME);
		}
	}
	else// if (displayLevel1Modes == false)
	{
		if (displayLevel1Modes == false)
		{
			Level_1_Text.setString("Level  1");
		}
		//displayLevelModes = false;
		levelHighlighted = false;
		Level_1_Text.setColor(sf::Color::White);
	}

	if (Level_2_Text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
	{
		if (levelHighlighted == false)
		{
			
			Level_2_Text.setColor(sf::Color::Yellow);
			SoundManager::GetInstance()->PlayClick();
			levelHighlighted = true;

			displayLevel1Modes = false;
			
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Level_2_Text.setString("Level 2 -> ");
			displayLevel2Modes = true;
			//LevelManager::GetInstance()->CreateLevel("Level1");
			//GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::GAME);
		}
	}
	else //if (displayLevel2Modes == false)
	{
		if (displayLevel2Modes == false)
		{
			Level_2_Text.setString("Level 2");
		}
		//displayLevelModes = false;
		levelHighlighted = false;
		Level_2_Text.setColor(sf::Color::White);
	}

	//LEVEL MODES
	if (displayLevel1Modes)
	{
		if (Level_1_Headshots_Text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
		{
			//Level_1_Headshots_Text.setString("->Level 1 - Headshots");
			Level_1_Headshots_Text.setColor(sf::Color::Yellow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//LevelManager::GetInstance()->CreateLevel("Level1");
				//GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::GAME);
			}
		}
		else
		{
			//Level_1_Headshots_Text.setString("Level 1 - Headshots");
			Level_1_Headshots_Text.setColor(sf::Color::White);
		}

		if (Level_1_Score_Text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
		{
			//Level_1_Score_Text.setString("->Level 1 - Highscore");
			Level_1_Score_Text.setColor(sf::Color::Yellow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				LevelManager::GetInstance()->CreateLevel("Level1");
				GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::GAME);
			}
		}
		else
		{
			//Level_1_Score_Text.setString("Level 1 - Highscore");
			Level_1_Score_Text.setColor(sf::Color::White);
		}

		if (Level_1_Speed_Text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
		{
			//Level_1_Speed_Text.setString("->Level 1 - Highspeed");
			Level_1_Speed_Text.setColor(sf::Color::Yellow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//LevelManager::GetInstance()->CreateLevel("Level1");
				//GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::GAME);
			}
		}
		else
		{
			//Level_1_Speed_Text.setString("Level 1 - Highspeed");
			Level_1_Speed_Text.setColor(sf::Color::White);
		}
	}

	if (displayLevel2Modes)
	{
		if (Level_2_Headshots_Text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
		{
			//Level_1_Headshots_Text.setString("->Level 1 - Headshots");
			Level_2_Headshots_Text.setColor(sf::Color::Yellow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//LevelManager::GetInstance()->CreateLevel("Level1");
				//GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::GAME);
			}
		}
		else
		{
			//Level_1_Headshots_Text.setString("Level 1 - Headshots");
			Level_2_Headshots_Text.setColor(sf::Color::White);
		}

		if (Level_2_Score_Text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
		{
			//Level_1_Score_Text.setString("->Level 1 - Highscore");
			Level_2_Score_Text.setColor(sf::Color::Yellow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//LevelManager::GetInstance()->CreateLevel("Level1");
				//GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::GAME);
			}
		}
		else
		{
			//Level_1_Score_Text.setString("Level 1 - Highscore");
			Level_2_Score_Text.setColor(sf::Color::White);
		}

		if (Level_2_Speed_Text.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
		{
			//Level_1_Speed_Text.setString("->Level 1 - Highspeed");
			Level_2_Speed_Text.setColor(sf::Color::Yellow);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//LevelManager::GetInstance()->CreateLevel("Level1");
				//GameStateManager::GetInstance()->SetGameState(GameStateManager::GameStates::GAME);
			}
		}
		else
		{
			//Level_1_Speed_Text.setString("Level 1 - Highspeed");
			Level_2_Speed_Text.setColor(sf::Color::White);
		}
	}
}