#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "BulletHole.h"

BulletHole::BulletHole()
{
	targetCollided = 0;
}

//! Setup each bullet hole sprite
/*!
\When called, sets the texture type, position(crosshair pos), origin (to centre of sprite)
\return none
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
	bulletHoleSprite.setScale(0.25, 0.25);
}

//! Draw the bullet holes
/*!
\Draws the bullet holes on to the window
\return none
\sa
*/
void BulletHole::Draw(sf::RenderWindow& window)
{
	//if (targetCollided != 0)
	window.draw(bulletHoleSprite);
}

void BulletHole::SetBulletTargetCollision(int targetNumber)
{
	targetCollided = targetNumber;
	cout << "Target Num: " << targetCollided << endl;
}

sf::Vector2f BulletHole::GetBulletPosition()
{
	return bulletHoleSprite.getPosition();
}