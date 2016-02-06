#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "Target.h"

Target::Target()
{

}

//! Set up the target sprite
/*!
\Sets the texture and position for the target sprite
\return none
\sa
*/
void Target::SetUp(sf::Vector2f targetPos, sf::Texture* targetImage, sf::Texture* bulletImage, float health, int layer)
{
	targetHealth = health;
	targetSprite.setTexture(*targetImage, true);
	targetSprite.setPosition(targetPos.x - targetSprite.getGlobalBounds().width / 2, targetPos.y);
	bulletWoodTexture = bulletImage;
	targetLayer = layer;
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
	for (BulletHole* b : bullets)
	{
		b->Draw(window);
	}
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

int Target::GetLayer()
{
	return targetLayer;
}

void Target::SetPosition(sf::Vector2f pos)
{
	targetSprite.setPosition(pos);
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

float Target::GetHealth()
{
	return targetHealth;
}

void Target::SetHealth()
{
	targetHealth -= 20;
}

void Target::AddBullet(sf::Vector2f pos)
{
	BulletHole* b = new BulletHole(pos, bulletWoodTexture);
	bullets.push_back(b);
}