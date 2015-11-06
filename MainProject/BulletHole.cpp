#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "BulletHole.h"

BulletHole::BulletHole()
{

}

//void BulletHole::SetUp()
//{
//	bulletMetalSprite.setTexture(bulletMetalImage, true);
//	bulletWoodSprite.setTexture(bulletWoodImage, true);
//
//	bulletMetalSprite.setOrigin(bulletMetalSprite.getGlobalBounds().width / 2, bulletMetalSprite.getGlobalBounds().height / 2);
//	bulletWoodSprite.setOrigin(bulletWoodSprite.getGlobalBounds().width / 2, bulletWoodSprite.getGlobalBounds().height / 2);
//
//	bulletMetalSprite.setScale(0.5, 0.5);
//	bulletWoodSprite.setScale(0.5, 0.5);
//}

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

void BulletHole::Draw(sf::RenderWindow& window)
{
	window.draw(bulletHoleSprite);
}