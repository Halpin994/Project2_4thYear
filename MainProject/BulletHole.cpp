#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "BulletHole.h"

BulletHole::BulletHole()
{

}

//! Overload function
/*!
\When called, sets the texture type, position(crosshair pos), origin (to centre of sprite)
\return none
\sa
*/
BulletHole::BulletHole(sf::Vector2f bulletPos, sf::Texture* bulletImage)
{
	bulletHoleSprite.setTexture(*bulletImage, true);
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

sf::Vector2f BulletHole::GetBulletPosition()
{
	return bulletHoleSprite.getPosition();
}