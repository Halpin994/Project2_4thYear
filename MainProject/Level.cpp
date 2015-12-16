#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "Level.h"
#include "TargetManager.h"

//! Default Constructor
/*!
\When called, this sets its self up through calling the load and set up functions
\return none
\sa
*/
Level::Level()
{
	Load();
	SetUp();
}

//! Load in assets
/*!
\Loads in the background image and assigns it to texture rangeImage
\return none
\sa
*/
void Level::Load()
{
	rangeTexture.loadFromFile("Assets/Images/Game/basicRange.png");
}

//! Setup the level's range sprite
/*!
\Set the sprites texture to the rangeImage loaded in the load() function.
\return none
\sa
*/
void Level::SetUp()
{
	rangeSprite.setTexture(rangeTexture, true);
	TargetManager::GetInstance()->AddTargets(sf::Vector2f(395, 180), 100);
	TargetManager::GetInstance()->AddTargets(sf::Vector2f(600, 180), 100);
	TargetManager::GetInstance()->AddTargets(sf::Vector2f(810, 180), 100);
}

//! Draw the level
/*!
\Draw the level range sprite relative to the window
\return none
\sa
*/
void Level::Draw(sf::RenderWindow& window)
{
	//rangeSprite.setPosition(0, 0);
	window.draw(rangeSprite);
}