#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "Level.h"

Level::Level()
{
	Load();
	SetUp();
}

void Level::Load()
{
	rangeImage.loadFromFile("basicRange.png");
}

void Level::SetUp()
{
	rangeSprite.setTexture(rangeImage, true);
}

void Level::Draw(sf::RenderWindow& window)
{
	rangeSprite.setPosition(0, 0);
	window.draw(rangeSprite);
}