#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "BulletHole.h"

BulletHole::BulletHole()
{

}

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
void BulletHole::SetUp(int textureType, sf::Vector2f bulletPos, sf::Texture* bulletMetalImage, sf::Texture* bulletWoodImage)
{
	if (textureType == 1)
		bulletHoleSprite.setTexture(*bulletMetalImage, true);
	if (textureType == 2)
		bulletHoleSprite.setTexture(*bulletWoodImage, true);

	bulletHoleSprite.setPosition(bulletPos);
	bulletHoleSprite.setOrigin(bulletHoleSprite.getGlobalBounds().width / 2, bulletHoleSprite.getGlobalBounds().height / 2);
	bulletHoleSprite.setScale(0.38, 0.38);
}

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
void BulletHole::Draw(sf::RenderWindow& window)
{
	window.draw(bulletHoleSprite);
}