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

//! Load the target
/*!
\Load in the target image and assign it to its relative texture
\return none
\sa
*/
void Target::Load()
{
	targetTexture.loadFromFile("target.png");
}

//! Set up the target sprite
/*!
\Sets the texture and position for the target sprite
\return none
\sa
*/
void Target::SetUp()
{
	targetSprite.setTexture(targetTexture, true);
	targetSprite.setPosition(600 - targetSprite.getGlobalBounds().width / 2, 180);
}

//! Draw the target
/*!
\Draws the target Sprite on the window
\return none
\sa
*/
void Target::Draw(sf::RenderWindow& window)
{
	window.draw(targetSprite);
}

//! Get the target position
/*!
\Returns the target sprite's position when called
\return Vector2f
\sa
*/
sf::Vector2f Target::GetPosition()
{
	return targetSprite.getPosition();
}

//! Get target width
/*!
\Returns the target sprite's width
\return float
\sa
*/
float Target::GetWidth()
{
	return targetSprite.getGlobalBounds().width;
}

//! Get target height
/*!
\Returns the target sprite's height
\return float
\sa
*/
float Target::GetHeight()
{
	return targetSprite.getGlobalBounds().height;
}