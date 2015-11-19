#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "Level.h"

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
Level::Level()
{
	Load();
	SetUp();
}

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
void Level::Load()
{
	rangeImage.loadFromFile("basicRange.png");
}

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
void Level::SetUp()
{
	rangeSprite.setTexture(rangeImage, true);
}

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
void Level::Draw(sf::RenderWindow& window)
{
	rangeSprite.setPosition(0, 0);
	window.draw(rangeSprite);
}