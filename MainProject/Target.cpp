#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "Target.h"

Target::Target()
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
void Target::Load()
{
	targetImage.loadFromFile("target.png");
}

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
void Target::SetUp()
{
	targetSprite.setTexture(targetImage, true);
	targetSprite.setPosition(600 - targetSprite.getGlobalBounds().width / 2, 180);
}

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
void Target::Draw(sf::RenderWindow& window)
{
	window.draw(targetSprite);
}

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
sf::Vector2f Target::GetPosition()
{
	return targetSprite.getPosition();
}

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
float Target::GetWidth()
{
	return targetSprite.getGlobalBounds().width;
}

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
float Target::GetHeight()
{
	return targetSprite.getGlobalBounds().height;
}