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
	timeToLive = 0.05;
	//if (targetLayer == 1)
	//{
	//	targetSprite.setScale(0.52, 0.52);
	//}
	//if (targetLayer == 3)
	//{
	//	targetSprite.setScale(2, 2);
	//}
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

void Target::Update(float ft)
{
	timeToLive -= ft;
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

sf::FloatRect Target::GetGlobalBounds()
{
	return targetSprite.getGlobalBounds();
}

int Target::GetLayer()
{
	return targetLayer;
}

float Target::GetTimeToLive()
{
	return timeToLive;
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
	targetHealth -= 25;
}

void Target::AddBullet(sf::Vector2f pos, static int bulletType)
{
	BulletHole* b = new BulletHole(pos, bulletType, bulletWoodTexture);
	bullets.push_back(b);
}